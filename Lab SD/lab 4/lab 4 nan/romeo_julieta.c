/*
*	Created by Nan Mihai on 16.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include "queue.h"

Point applyDirection(Point point, Point direction) {
	point.x += direction.x;
	point.y += direction.y;
	return point;
}

int checkPoint(Point point, int width, int height) {
	if (point.x < 0 || point.y < 0)
		return 0;
	if (point.x >= width || point.y >= height)
		return 0;
	return 1;
}

void Lee(Queue queue, int **map, int width, int height, Point directions[]) {
	//TODO - Problema 4
}

int main(int argc, char **argv) {
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);
	Point directions[8];
	directions[0].x = 0;
	directions[0].y = 1;
	directions[1].x = 0;
	directions[1].y = -1;
	directions[2].x = 1;
	directions[2].y = 0;
	directions[3].x = -1;
	directions[3].y = 0;
	directions[4].x = 1;
	directions[4].y = 1;
	directions[5].x = 1;
	directions[5].y = -1;
	directions[6].x = -1;
	directions[6].y = 1;
	directions[7].x = -1;
	directions[7].y = -1;

	int **JulietMap, **RomeoMap;
	int width, height, i, j;
	char character;
	Queue RomeoQueue, JulietQueue;
	Point point;
	int tmin = 9999;

	RomeoQueue = initQueue(SIZE);
	JulietQueue = initQueue(SIZE);

	scanf("%d %d\n", &width, &height);
	RomeoMap = (int**) malloc(width * sizeof(int *));
	JulietMap = (int**) malloc(width * sizeof(int *));
	for (i = 0; i < width; i++) {
		RomeoMap[i] = (int*) malloc(height * sizeof(int));
		JulietMap[i] = (int*) malloc(height * sizeof(int));
		for (j = 0; j < height; j++) {
			scanf("%c", &character);
			if (character == 'X') {
				JulietMap[i][j] = -1;
				RomeoMap[i][j] = -1;
			} else if (character == 'R') {
				RomeoMap[i][j] = 1;
				JulietMap[i][j] = 0;
				point.x = i;
				point.y = j;
				RomeoQueue = enqueue(RomeoQueue, point);
			} else if (character == 'J') {
				RomeoMap[i][j] = 0;
				JulietMap[i][j] = 1;
				point.x = i;
				point.y = j;
				JulietQueue = enqueue(JulietQueue, point);
			} else {
				RomeoMap[i][j] = 0;
				JulietMap[i][j] = 0;
			}
		}
		scanf("%c", &character);
	}

	Lee(RomeoQueue, RomeoMap, width, height, directions);
	Lee(JulietQueue, JulietMap, width, height, directions);
	RomeoQueue = freeQueue(RomeoQueue);
	JulietQueue = freeQueue(JulietQueue);

	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			if ((RomeoMap[i][j] == JulietMap[i][j]) && RomeoMap[i][j] < tmin && RomeoMap[i][j] > 0) {
				tmin = RomeoMap[i][j];
				point.x = i + 1;
				point.y = j + 1;
			}
		}
	}

	printf("%d %d %d\n", tmin, point.x, point.y);

	for (i = 0; i < width; i++) {
		free(RomeoMap[i]);
		free(JulietMap[i]);
	}
	free(RomeoMap);
	free(JulietMap);

 	return 0;
}
