#include <iostream>
#include <math.h>
using namespace std;

class Vector3D {
public:
	double X;
	double Y;
	double Z;
	void input(double A, double B, double C) {
		X = A;
		Y = B;
		Z = C;
	}
	void output() {
		cout << X << "\t" << Y << "\t" << Z << endl;
	}
};


class Segment3D {
public:
	Vector3D start;
	Vector3D end;
	void input(Vector3D A, Vector3D B) {
		start = A;
		end = B;
	}
	void output() {
		start.output();
		end.output();
	}
};

bool plane(Segment3D A, Segment3D B) {
	double res;
	res = (A.end.X - A.start.X) * (B.start.Y - A.start.Y) * (B.end.Z - A.start.Z)
		+ (B.end.X - A.start.X) * (A.end.Y - A.start.Y) * (B.start.Z - A.start.Z)
		+ (A.end.Z - A.start.Z) * (B.start.X - B.start.X) * (B.end.Y - A.start.Y)
		- (B.end.X - A.start.X) * (B.start.Y - A.start.Y) * (A.end.Z - A.start.Z)
		- (B.start.X - B.start.X) * (A.end.Y - A.start.Y) * (B.end.Z - A.start.Z)
		- (A.end.X - A.start.X) * (B.start.Z - A.start.Z) * (B.end.Y - A.start.Y);
	if (res == 0) {
		cout << "in same plane" << endl; return true;
	}
	else {
		cout << "in different plane" << endl; return false;
	}
}

bool equalV(Vector3D A, Vector3D B) {
	if ((A.X == B.X) && (A.Y == B.Y) && (A.Z == B.Z)) return true;
	else return false;
}
bool equalS(Segment3D A, Segment3D B) {
	if (equalV(A.start, B.start)) { A.start.output(); return true; }
	else if (equalV(A.start, B.end)) { A.start.output(); return true; }
	else if (equalV(A.end, B.start)) { A.end.output(); return true; }
	else if (equalV(A.end, B.end)) { A.end.output(); return true; }
	else return false;
}

void cross(Segment3D A, Segment3D B) {
	double U, V, W;
	double q1, q2, s1;
	if ((A.start.X - A.end.X) * (B.end.Y - B.start.Y) - (B.end.X - B.start.X) * (A.start.Y - A.end.Y) != 0) {
		q1 = (B.end.X - A.end.X) * (B.end.Y - B.start.Y) - (B.end.X - B.start.X) * (B.end.Y - A.end.Y);
		q2 = (A.start.X - A.end.X) * (B.end.Y - B.start.Y) - (B.end.X - B.start.X) * (A.start.Y - A.end.Y);
		s1 = (A.start.X - A.end.X) * (B.end.Y - A.end.Y) - (B.end.X - A.end.X) * (A.start.Y - A.end.Y);
		if ((q1 / q2 <= 1) && (s1 / q2 <= 1)) {
			U = q1 / q2 * (A.start.X - A.end.X) + A.end.X;
			V = q1 / q2 * (A.start.Y - A.end.Y) + A.end.Y;
			W = q1 / q2 * (A.start.Z - A.end.Z) + A.end.Z;
			cout << U << "\t" << V << "\t" << W << endl;
		}
		else cout << "Don't intersect" << endl;
	}
	else if ((A.start.Y - A.end.Y) * (B.end.Z - B.start.Z) - (B.end.Y - B.start.Y) * (A.start.Z - A.end.Z) != 0) {
		q1 = (B.end.Y - A.end.Y) * (B.end.Z - B.start.Z) - (B.end.Y - B.start.Y) * (B.end.Z - A.end.Z);
		q2 = (A.start.Y - A.end.Y) * (B.end.Z - B.start.Z) - (B.end.Y - B.start.Y) * (A.start.Z - A.end.Z);
		s1 = (A.start.Y - A.end.Y) * (B.end.Z - A.end.Z) - (B.end.Y - A.end.Y) * (A.start.Z - A.end.Z);
		if ((q1 / q2 <= 1) && (s1 / q2 <= 1)) {
			U = q1 / q2 * (A.start.X - A.end.X) + A.end.X;
			V = q1 / q2 * (A.start.Y - A.end.Y) + A.end.Y;
			W = q1 / q2 * (A.start.Z - A.end.Z) + A.end.Z;
			cout << U << "\t" << V << "\t" << W << endl;
		}
		else cout << "Don't intersect" << endl;
	}
	else if ((A.start.Z - A.end.Z) * (B.end.X - B.start.X) - (B.end.Z - B.start.Z) * (A.start.X - A.end.X) != 0) {
		q1 = (B.end.Z - A.end.Z) * (B.end.X - B.start.X) - (B.end.Z - B.start.Z) * (B.end.X - A.end.X);
		q2 = (A.start.Z - A.end.Z) * (B.end.X - B.start.X) - (B.end.Z - B.start.Z) * (A.start.X - A.end.X);
		s1 = (A.start.Z - A.end.Z) * (B.end.X - A.end.X) - (B.end.Z - A.end.Z) * (A.start.X - A.end.X);
		if ((q1 / q2 <= 1) && (s1 / q2 <= 1)) {
			U = q1 / q2 * (A.start.X - A.end.X) + A.end.X;
			V = q1 / q2 * (A.start.Y - A.end.Y) + A.end.Y;
			W = q1 / q2 * (A.start.Z - A.end.Z) + A.end.Z;
			cout << U << "\t" << V << "\t" << W << endl;
		}
		else cout << "Don't intersect" << endl;
	}
	else cout << "Don't intersect" << endl;
}

bool match(Segment3D A, Segment3D B) {
	//случаи частичного наложения
	//случай 1
	if ((A.start.X <= B.start.X) && (B.start.X <= A.end.X) && (A.end.X <= B.end.X)
		&& (A.start.Y <= B.start.Y) && (B.start.Y <= A.end.Y) && (A.end.Y <= B.end.Y)
		&& (A.start.Z <= B.start.Z) && (B.start.Z <= A.end.Z) && (A.end.Z <= B.end.Z))
	{
		cout << "Multiplicity: [C; B]" << endl; return true;
	}
	//случай 2
	else if ((A.start.X <= B.end.X) && (B.end.X <= A.end.X) && (A.end.X <= B.start.X)
		&& (A.start.Y <= B.end.Y) && (B.end.Y <= A.end.Y) && (A.end.Y <= B.start.Y)
		&& (A.start.Z <= B.end.Z) && (B.end.Z <= A.end.Z) && (A.end.Z <= B.start.Z))
	{
		cout << "Multiplicity: [D; B]" << endl; return true;
	}
	//случай 3
	else if ((A.end.X <= B.start.X) && (B.start.X <= A.start.X) && (A.start.X <= B.end.X)
		&& (A.end.Y <= B.start.Y) && (B.start.Y <= A.start.Y) && (A.start.Y <= B.end.Y)
		&& (A.end.Z <= B.start.Z) && (B.start.Z <= A.start.Z) && (A.start.Z <= B.end.Z))
	{
		cout << "Multiplicity: [C; A]" << endl; return true;
	}
	//случай 4
	else if ((A.end.X <= B.end.X) && (B.end.X <= A.start.X) && (A.start.X <= B.start.X)
		&& (A.end.Y <= B.end.Y) && (B.end.Y <= A.start.Y) && (A.start.Y <= B.start.Y)
		&& (A.end.Z <= B.end.Z) && (B.end.Z <= A.start.Z) && (A.start.Z <= B.start.Z))
	{
		cout << "Multiplicity: [D; A]" << endl; return true;
	}

	//симметричные случаи
	//случай 1
	else if ((A.start.X >= B.start.X) && (B.start.X >= A.end.X) && (A.end.X >= B.end.X)
		&& (A.start.Y >= B.start.Y) && (B.start.Y >= A.end.Y) && (A.end.Y >= B.end.Y)
		&& (A.start.Z >= B.start.Z) && (B.start.Z >= A.end.Z) && (A.end.Z >= B.end.Z))
	{
		cout << "Multiplicity: [B; C]" << endl; return true;
	}
	//случай 2
	else if ((A.start.X >= B.end.X) && (B.end.X >= A.end.X) && (A.end.X >= B.start.X)
		&& (A.start.Y >= B.end.Y) && (B.end.Y >= A.end.Y) && (A.end.Y >= B.start.Y)
		&& (A.start.Z >= B.end.Z) && (B.end.Z >= A.end.Z) && (A.end.Z >= B.start.Z))
	{
		cout << "Multiplicity: [B; D]" << endl; return true;
	}
	//случай 3
	else if ((A.end.X >= B.start.X) && (B.start.X >= A.start.X) && (A.start.X >= B.end.X)
		&& (A.end.Y >= B.start.Y) && (B.start.Y >= A.start.Y) && (A.start.Y >= B.end.Y)
		&& (A.end.Z >= B.start.Z) && (B.start.Z >= A.start.Z) && (A.start.Z >= B.end.Z))
	{
		cout << "Multiplicity: [A; C]" << endl; return true;
	}
	//случай 4
	else if ((A.end.X >= B.end.X) && (B.end.X >= A.start.X) && (A.start.X >= B.start.X)
		&& (A.end.Y >= B.end.Y) && (B.end.Y >= A.start.Y) && (A.start.Y >= B.start.Y)
		&& (A.end.Z >= B.end.Z) && (B.end.Z >= A.start.Z) && (A.start.Z >= B.start.Z))
	{
		cout << "Multiplicity: [A; D]" << endl; return true;
	}

	//случаи полного наложения
	//случай 1
	else if ((A.start.X <= B.start.X) && (B.start.X <= B.end.X) && (B.end.X <= A.end.X)
		&& (A.start.Y <= B.start.Y) && (B.start.Y <= B.end.Y) && (B.end.Y <= A.end.Y)
		&& (A.start.Z <= B.start.Z) && (B.start.Z <= B.end.Z) && (B.end.Z <= A.end.Z))
	{
		cout << "Multiplicity: [C; D]" << endl; return true;
	}
	//случай 2
	else if ((A.start.X <= B.end.X) && (B.end.X <= B.start.X) && (B.start.X <= A.end.X)
		&& (A.start.Y <= B.end.Y) && (B.end.Y <= B.start.Y) && (B.start.Y <= A.end.Y)
		&& (A.start.Z <= B.end.Z) && (B.end.Z <= B.start.Z) && (B.start.Z <= A.end.Z))
	{
		cout << "Multiplicity: [D; C]" << endl; return true;
	}
	//Случай 3
	else if ((B.start.X <= A.start.X) && (A.start.X <= A.end.X) && (A.end.X <= B.end.X)
		&& (B.start.Y <= A.start.Y) && (A.start.Y <= A.end.Y) && (A.end.Y <= B.end.Y)
		&& (B.start.Z <= A.start.Z) && (A.start.Z <= A.end.Z) && (A.end.Z <= B.end.Z))
	{
		cout << "Multiplicity: [A; B]" << endl; return true;
	}
	//случай 4
	else if ((B.start.X <= A.end.X) && (A.end.X <= A.start.X) && (A.start.X <= B.end.X)
		&& (B.start.Y <= A.end.Y) && (A.end.Y <= A.start.Y) && (A.start.Y <= B.end.Y)
		&& (B.start.Z <= A.end.Z) && (A.end.Z <= A.start.Z) && (A.start.Z <= B.end.Z))
	{
		cout << "Multiplicity: [B; A]" << endl; return true;
	}

	//симметричные случаи
	//случай 1
	else if ((A.end.X <= B.end.X) && (B.end.X <= B.start.X) && (B.start.X <= A.start.X)
		&& (A.end.Y <= B.end.Y) && (B.end.Y <= B.start.Y) && (B.start.Y <= A.start.Y)
		&& (A.end.Z <= B.end.Z) && (B.end.Z <= B.start.Z) && (B.start.Z <= A.start.Z))
	{
		cout << "Multiplicity: [D; C]" << endl; return true;
	}
	//случай 2
	else if ((A.end.X <= B.start.X) && (B.start.X <= B.end.X) && (B.end.X <= A.start.X)
		&& (A.end.Y <= B.start.Y) && (B.start.Y <= B.end.Y) && (B.end.Y <= A.start.Y)
		&& (A.end.Z <= B.start.Z) && (B.start.Z <= B.end.Z) && (B.end.Z <= A.start.Z))
	{
		cout << "Multiplicity: [C; D]" << endl; return true;
	}
	//Случай 3
	else if ((B.end.X <= A.end.X) && (A.end.X <= A.start.X) && (A.start.X <= B.start.X)
		&& (B.end.Y <= A.end.Y) && (A.end.Y <= A.start.Y) && (A.start.Y <= B.start.Y)
		&& (B.end.Z <= A.end.Z) && (A.end.Z <= A.start.Z) && (A.start.Z <= B.start.Z))
	{
		cout << "Multiplicity: [B; A]" << endl; return true;
	}
	//случай 4
	else if ((B.end.X <= A.start.X) && (A.start.X <= A.end.X) && (A.end.X <= B.start.X)
		&& (B.end.Y <= A.start.Y) && (A.start.Y <= A.end.Y) && (A.end.Y <= B.start.Y)
		&& (B.end.Z <= A.start.Z) && (A.start.Z <= A.end.Z) && (A.end.Z <= B.start.Z))
	{
		cout << "Multiplicity: [A; B]" << endl; return true;
	}
	else return false;
}




int main() {
	Segment3D first, second;
	Vector3D a, b, c, d;
	double a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3;
	cout << "A" << "\t"; cin >> a1 >> a2 >> a3;
	cout << "B" << "\t"; cin >> b1 >> b2 >> b3;
	cout << "C" << "\t"; cin >> c1 >> c2 >> c3;
	cout << "D" << "\t"; cin >> d1 >> d2 >> d3;
	a.input(a1, a2, a3);
	b.input(b1, b2, b3);
	c.input(c1, c2, c3);
	d.input(d1, d2, d3);
	first.input(a, b);
	second.input(c, d);
	if (equalS(first, second)) cout << "Identical border" << endl;
	else if (!match(first, second)) {
		if (plane(first, second)) cross(first, second);
	}
	//else cout << "Don't intersect" << endl;
}
