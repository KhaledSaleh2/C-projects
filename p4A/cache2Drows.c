// Khaled Saleh

#define GLOBAL_ROWS 3000
#define GLOBAL_COLS 500

int global_2d[GLOBAL_ROWS][GLOBAL_COLS];

int main() {
	for (int i = 0; i < GLOBAL_ROWS; i++) {
		for (int j = 0; j < GLOBAL_COLS; j++) {
			global_2d[i][j] = i + j;
		}
	}
	return 0;
}
