#pragma once

template<typename T, int X, int Y=X>
class Matrix {
private:
	T data[Y*X];
public:
	
	Matrix(T defaultValue=T()) {
		for (int i = 0; i < X*Y; i++) {
			data[i] = defaultValue;
		}
	}
	
	T get(int x, int y) {
		return data[y * X + x];
	}
	
	void set(int x, int y, T value) {
		data[y * X + x] = value;
	}
};

template<typename T>
class VMatrix {
private:
	T* data;
	int X, Y;
public:
	VMatrix(int X, int Y, T defaultValue=T()) {
		data = new T[X*Y];
		this->X = X;
		this->Y = Y;
		for (int i = 0; i < X*Y; i++) {
			data[i] = defaultValue;
		}
	}
	
	T get(int x, int y) {
		return data[y * X + x];
	}
	
	void set(int x, int y, T value) {
		data[y * X + x] = value;
	}
	
	int getX() {
		return X;
	}
	
	int getY() {
		return Y;
	}
};
