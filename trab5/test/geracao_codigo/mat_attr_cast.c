mat int mi[12][23];
int main() {
	// mat int mi[12][23];
	mat int mi_local[5][5];
	mat float mf[1][1];
	mat float mg[2][4];
	// mi = mf;
	mf = mi;
	mg = mi;
	mf = mi_local;
}