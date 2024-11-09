// Khaled Saleh

#define ROWS 3000
#define COLS 500

int arr2d[ROWS][COLS];

int main() {
	for (int col = 0; col < COLS; col++) {
		for (int row = 0; row < ROWS; row++) {
			arr2d[row][col] = row + col;
		}
	}
	return 0;
}
