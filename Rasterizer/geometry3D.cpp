#include "geometry3D.h"

Triangle3D::Triangle3D(Point3D A, Point3D B, Point3D C) {
	vertexes[0] = A;
	vertexes[1] = B;
	vertexes[2] = C;
}

Point3D operator+(Point3D a, Point3D b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Point3D operator-(Point3D a, Point3D b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Collection::Collection() {
}

Collection::Collection(Point3D* vertexes, int vertexCount, int** faces, int faceCount) {
	this->vertexCount = vertexCount;
	this->faceCount = faceCount;

	if (this->vertexes)
		delete[] this->vertexes;

	if (this->faces) {
		for (int i = 0; i < faceCount; i++) {
			delete[] this->faces;
		}
	}

	this->vertexes = new Point3D[vertexCount];
	this->faces = new int*[faceCount];


	for (int i = 0; i < vertexCount; i++) {
		this->vertexes[i] = vertexes[i];
	}

	for (int i = 0; i < faceCount; i++) {
		this->faces[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			this->faces[i][j] = faces[i][j];
		}
	}

}

Triangle3D Collection::GetFace(int index) {
	if (index <= faceCount) {
		return Triangle3D(
			vertexes[faces[index][0]],
			vertexes[faces[index][1]],
			vertexes[faces[index][2]]
		);
	}
}

Collection::~Collection() {
	if (vertexes)
		delete[] vertexes;

	if (faces) {
		for (int i = 0; i < faceCount; i++) {
			delete[] faces[i];
		}
	}
}

void Collection::AddFace(Triangle3D triangle) {
	
	int** tempFaces = new int* [faceCount];
	for (int i = 0; i < faceCount; i++) {
		tempFaces[i] = new int[3];
	}
	Point3D* tempVertexes = new Point3D[vertexCount];

	// copy old arrays to temp arrays
	for (int i = 0; i < faceCount; i++) {
		for (int j = 0; j < 3; j++) {
			tempFaces[i][j] = faces[i][j];
		}
	}

	for (int i = 0; i < vertexCount; i++) {
		tempVertexes[i] = vertexes[i];
	}

	// delete old arrays
	if (vertexes)
		delete[] vertexes;
	vertexes = nullptr;

	if (faces) {
		for (int i = 0; i < faceCount; i++) {
			delete[] faces[i];
		}
	}
	faces = nullptr;
	
	// remake old arrays

	vertexes = new Point3D[vertexCount + 3];
	faces = new int* [faceCount + 1];
	for (int i = 0; i < faceCount + 1; i++) {
		faces[i] = new int[3];
	}

	// copy old
	for (int i = 0; i < vertexCount; i++) {
		vertexes[i] = tempVertexes[i];
	}

	delete[] tempVertexes;

	for (int i = 0; i < faceCount; i++) {
		for (int j = 0; j < 3; j++) {
			faces[i][j] = tempFaces[i][j];
			
		}
		delete[] tempFaces[i];
	}
	delete[] tempFaces;
	tempFaces = nullptr;

	// add new face to the end
	for (int i = 0; i < 3; i++) {
		vertexes[vertexCount + i] = triangle.vertexes[i];
	}

	for (int i = 0; i < 3; i++) {
		faces[faceCount][i] = vertexCount + i;
	}

	vertexCount += 3;
	faceCount++;
}