#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// 移动枚举量：抽象化具体输入，避免与特定窗口系统（如GLFW）耦合
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// 默认相机参数
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

static glm::mat4 myLookAt(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 Up)
{
	// 1. 计算相机坐标系的三个轴（正交基）
	// 注意：OpenGL 中相机看向 -Z 方向，所以 zaxis 是从目标指向相机的向量（正Z）
	glm::vec3 zaxis = glm::normalize(cameraPos - cameraTarget);

	// 计算右向量 (xaxis)：由“世界向上向量”与“相机Z轴”叉乘得到
	glm::vec3 xaxis = glm::normalize(glm::cross(Up, zaxis));

	// 计算相机自身的向上向量 (yaxis)：由 Z 轴与 X 轴叉乘得到
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	// 2. 创建平移矩阵 (Translation)
	// 目的：将相机移动到世界原点。位移量是相机位置的负值
	// GLM 采用列主序存储：mat[列][行]
	glm::mat4 translation = glm::mat4(1.0f);
	translation[3][0] = -cameraPos.x; // 第4列，第1行
	translation[3][1] = -cameraPos.y; // 第4列，第2行
	translation[3][2] = -cameraPos.z; // 第4列，第3行

	// 3. 创建旋转矩阵 (Rotation)
	// 目的：将世界坐标轴对齐到相机的方向轴
	// 这是一个正交矩阵的转置（即逆矩阵），用于把世界基向量变换到相机基向量
	glm::mat4 rotation = glm::mat4(1.0f);

	// 第一行：填充 xaxis (右向量)
	rotation[0][0] = xaxis.x; rotation[1][0] = xaxis.y; rotation[2][0] = xaxis.z;

	// 第二行：填充 yaxis (上向量)
	rotation[0][1] = yaxis.x; rotation[1][1] = yaxis.y; rotation[2][1] = yaxis.z;

	// 第三行：填充 zaxis (前向量/后退方向)
	rotation[0][2] = zaxis.x; rotation[1][2] = zaxis.y; rotation[2][2] = zaxis.z;

	// 4. 返回最终的观察矩阵 (LookAt Matrix)
	// 变换顺序：先平移再旋转。在线性代数中，矩阵从右向左读取：Rotation * Translation
	return rotation * translation;
}

// 抽象相机类：处理输入并计算对应的欧拉角、向量和矩阵，供 OpenGL 使用
class Camera
{
public:
	// 相机属性
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// 欧拉角
	float Yaw;
	float Pitch;
	// 相机配置选项
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// 构造函数（向量方式）
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// 构造函数（标量方式）
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// 返回由欧拉角和 LookAt 矩阵计算出的观察矩阵
	glm::mat4 GetViewMatrix()
	{
		return myLookAt(Position, Position + Front, Up);
	}

	// 处理键盘输入：接收自定义的枚举方向和 deltaTime（保证移动平滑）
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;

		//如果不加这一行：在第一人称视角中，如果你正抬头看着天空（Front 向量指向斜上方）按“前进”键，相机不仅会向前走，还会飞上天。同理，低头走会钻进地里。加上这一行后：实现“步行”效果：玩家只能在 $XZ$ 平面（地面）移动。即使你仰望星空按 W 键，你也只是在地面上向前挪动，而不会真的飞起来。
		Position.y = 0.0f;
	}

	// 处理鼠标移动：接收 X 和 Y 方向的偏移量
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// 限制俯仰角，防止屏幕翻转
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// 更新完欧拉角后，重新计算相机的三个向量
		updateCameraVectors();
	}

	// 处理鼠标滚轮：只需垂直方向的偏移量，用于实现缩放 (Zoom) 效果
	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

private:
	// 根据相机（更新后的）欧拉角计算 Front 向量
	void updateCameraVectors()
	{
		// 计算新的 Front 向量
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		// 重新计算相机的 Right 和 Up 向量
		// 必须归一化，因为抬头或低头时叉乘结果长度会变短，导致移动速度变慢
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif