#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Vector3D {
private:
	double X = 0;
	double Y = 0;
	double Z = 0;
public:
	Vector3D() {}
	Vector3D(double X, double Y, double Z) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	Vector3D(const Vector3D& other) {
		this->X = other.X;
		this->Y = other.Y;
		this->Z = other.Z;
	}
	double GetX() {
		return X;
	}
	double GetY() {
		return Y;
	}
	double GetZ() {
		return Z;
	}
	double SetX(double X) {
		this->X = X;
	}
	double SetY(double Y) {
		this->Y = Y;
	}
	double SetZ(double Z) {
		this->Z = Z;
	}

	bool operator==(const Vector3D& other) {
		if (this->X != other.X || this->Y != other.Y || this->Z != other.Z)
			return false;
		return true;
	}
	bool operator!=(const Vector3D& other) {
		if (this->X != other.X || this->Y != other.Y || this->Z != other.Z)
			return true;
		return false;
	}
};


class Segment3D {
private:
	Vector3D start;
	Vector3D end;

	/// <summary>
	/// проверка отрезков на принадлежность одной плоскости.
	/// </summary>
	/// <param name="A">другой отрезок</param>
	/// <returns>true - в одной плоскости, false - скрещивающиеся отрезки</returns>
	bool Plane(Segment3D A) {
		double res;
		res = (end.GetX() - start.GetX()) * (A.start.GetY() - start.GetY()) * (A.end.GetZ() - start.GetZ()) +
			(end.GetY() - start.GetY()) * (A.start.GetZ() - start.GetZ()) * (A.end.GetX() - start.GetX()) +
			(end.GetZ() - start.GetZ()) * (A.start.GetX() - start.GetX()) * (A.end.GetY() - start.GetY()) -
			(end.GetZ() - start.GetZ()) * (A.start.GetY() - start.GetY()) * (A.end.GetX() - start.GetX()) -
			(end.GetX() - start.GetX()) * (A.start.GetZ() - start.GetZ()) * (A.end.GetY() - start.GetY()) -
			(end.GetY() - start.GetY()) * (A.start.GetX() - start.GetX()) * (A.end.GetZ() - start.GetZ());
		if (res == 0) {
			//cout << "in same plane" << endl; 
			return true;
		}
		else {
			//cout << "in different plane" << endl; 
			return false;
		}
	}

	/// <summary>
	/// Находит наложение отрезков. Если есть наложение кидает exception.
	/// </summary>
	/// <param name="A">другой отрезок</param>
	/// <returns>false - нет наложений (нет бесконечного множества точек пересечения)</returns>
	bool Match(Segment3D A) {
		//случаи частичного наложения
		//случай 1
		if ((start.GetX() <= A.start.GetX()) && (A.start.GetX() <= end.GetX()) && (end.GetX() <= A.end.GetX())
			&& (start.GetY() <= A.start.GetY()) && (A.start.GetY() <= end.GetY()) && (end.GetY() <= A.end.GetY())
			&& (start.GetZ() <= A.start.GetZ()) && (A.start.GetZ() <= end.GetZ()) && (end.GetZ() <= A.end.GetZ()))
		{
			//cout << "Multiplicity: [C; B]" << endl; 
			throw exception("Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return end;
		}
		//случай 2
		else if ((start.GetX() <= A.end.GetX()) && (A.end.GetX() <= end.GetX()) && (end.GetX() <= A.start.GetX())
			&& (start.GetY() <= A.end.GetY()) && (A.end.GetY() <= end.GetY()) && (end.GetY() <= A.start.GetY())
			&& (start.GetZ() <= A.end.GetZ()) && (A.end.GetZ() <= end.GetZ()) && (end.GetZ() <= A.start.GetZ()))
		{
			//cout << "Multiplicity: [D; B]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return end;
		}
		//случай 3
		else if ((end.GetX() <= A.start.GetX()) && (A.start.GetX() <= start.GetX()) && (start.GetX() <= A.end.GetX())
			&& (end.GetY() <= A.start.GetY()) && (A.start.GetY() <= start.GetY()) && (start.GetY() <= A.end.GetY())
			&& (end.GetZ() <= A.start.GetZ()) && (A.start.GetZ() <= start.GetZ()) && (start.GetZ() <= A.end.GetZ()))
		{
			//cout << "Multiplicity: [C; A]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return start;
		}
		//случай 4
		else if ((end.GetX() <= A.end.GetX()) && (A.end.GetX() <= start.GetX()) && (start.GetX() <= A.start.GetX())
			&& (end.GetY() <= A.end.GetY()) && (A.end.GetY() <= start.GetY()) && (start.GetY() <= A.start.GetY())
			&& (end.GetZ() <= A.end.GetZ()) && (A.end.GetZ() <= start.GetZ()) && (start.GetZ() <= A.start.GetZ()))
		{
			//cout << "Multiplicity: [D; A]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return start;
		}

		//симметричные случаи
		//случай 1
		else if ((start.GetX() >= A.start.GetX()) && (A.start.GetX() >= end.GetX()) && (end.GetX() >= A.end.GetX())
			&& (start.GetY() >= A.start.GetY()) && (A.start.GetY() >= end.GetY()) && (end.GetY() >= A.end.GetY())
			&& (start.GetZ() >= A.start.GetZ()) && (A.start.GetZ() >= end.GetZ()) && (end.GetZ() >= A.end.GetZ()))
		{
			//cout << "Multiplicity: [B; C]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return end;
		}
		//случай 2
		else if ((start.GetX() >= A.end.GetX()) && (A.end.GetX() >= end.GetX()) && (end.GetX() >= A.start.GetX())
			&& (start.GetY() >= A.end.GetY()) && (A.end.GetY() >= end.GetY()) && (end.GetY() >= A.start.GetY())
			&& (start.GetZ() >= A.end.GetZ()) && (A.end.GetZ() >= end.GetZ()) && (end.GetZ() >= A.start.GetZ()))
		{
			//cout << "Multiplicity: [B; D]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return end;
		}
		//случай 3
		else if ((end.GetX() >= A.start.GetX()) && (A.start.GetX() >= start.GetX()) && (start.GetX() >= A.end.GetX())
			&& (end.GetY() >= A.start.GetY()) && (A.start.GetY() >= start.GetY()) && (start.GetY() >= A.end.GetY())
			&& (end.GetZ() >= A.start.GetZ()) && (A.start.GetZ() >= start.GetZ()) && (start.GetZ() >= A.end.GetZ()))
		{
			//cout << "Multiplicity: [A; C]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return start;
		}
		//случай 4
		else if ((end.GetX() >= A.end.GetX()) && (A.end.GetX() >= start.GetX()) && (start.GetX() >= A.start.GetX())
			&& (end.GetY() >= A.end.GetY()) && (A.end.GetY() >= start.GetY()) && (start.GetY() >= A.start.GetY())
			&& (end.GetZ() >= A.end.GetZ()) && (A.end.GetZ() >= start.GetZ()) && (start.GetZ() >= A.start.GetZ()))
		{
			//cout << "Multiplicity: [A; D]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return start;
		}

		//случаи полного наложения
		//случай 1
		else if ((start.GetX() <= A.start.GetX()) && (A.start.GetX() <= A.end.GetX()) && (A.end.GetX() <= end.GetX())
			&& (start.GetY() <= A.start.GetY()) && (A.start.GetY() <= A.end.GetY()) && (A.end.GetY() <= end.GetY())
			&& (start.GetZ() <= A.start.GetZ()) && (A.start.GetZ() <= A.end.GetZ()) && (A.end.GetZ() <= end.GetZ()))
		{
			//cout << "Multiplicity: [C; D]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return A.start;
		}
		//случай 2
		else if ((start.GetX() <= A.end.GetX()) && (A.end.GetX() <= A.start.GetX()) && (A.start.GetX() <= end.GetX())
			&& (start.GetY() <= A.end.GetY()) && (A.end.GetY() <= A.start.GetY()) && (A.start.GetY() <= end.GetY())
			&& (start.GetZ() <= A.end.GetZ()) && (A.end.GetZ() <= A.start.GetZ()) && (A.start.GetZ() <= end.GetZ()))
		{
			//cout << "Multiplicity: [D; C]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return A.start;
		}
		//Случай 3
		else if ((A.start.GetX() <= start.GetX()) && (start.GetX() <= end.GetX()) && (end.GetX() <= A.end.GetX())
			&& (A.start.GetY() <= start.GetY()) && (start.GetY() <= end.GetY()) && (end.GetY() <= A.end.GetY())
			&& (A.start.GetZ() <= start.GetZ()) && (start.GetZ() <= end.GetZ()) && (end.GetZ() <= A.end.GetZ()))
		{
			//cout << "Multiplicity: [A; B]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return start;
		}
		//случай 4
		else if ((A.start.GetX() <= end.GetX()) && (end.GetX() <= start.GetX()) && (start.GetX() <= A.end.GetX())
			&& (A.start.GetY() <= end.GetY()) && (end.GetY() <= start.GetY()) && (start.GetY() <= A.end.GetY())
			&& (A.start.GetZ() <= end.GetZ()) && (end.GetZ() <= start.GetZ()) && (start.GetZ() <= A.end.GetZ()))
		{
			//cout << "Multiplicity: [B; A]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return start;
		}

		//симметричные случаи
		//случай 1
		else if ((end.GetX() <= A.end.GetX()) && (A.end.GetX() <= A.start.GetX()) && (A.start.GetX() <= start.GetX())
			&& (end.GetY() <= A.end.GetY()) && (A.end.GetY() <= A.start.GetY()) && (A.start.GetY() <= start.GetY())
			&& (end.GetZ() <= A.end.GetZ()) && (A.end.GetZ() <= A.start.GetZ()) && (A.start.GetZ() <= start.GetZ()))
		{
			//cout << "Multiplicity: [D; C]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return A.start;
		}
		//случай 2
		else if ((end.GetX() <= A.start.GetX()) && (A.start.GetX() <= A.end.GetX()) && (A.end.GetX() <= start.GetX())
			&& (end.GetY() <= A.start.GetY()) && (A.start.GetY() <= A.end.GetY()) && (A.end.GetY() <= start.GetY())
			&& (end.GetZ() <= A.start.GetZ()) && (A.start.GetZ() <= A.end.GetZ()) && (A.end.GetZ() <= start.GetZ()))
		{
			//cout << "Multiplicity: [C; D]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return A.start;
		}
		//Случай 3
		else if ((A.end.GetX() <= end.GetX()) && (end.GetX() <= start.GetX()) && (start.GetX() <= A.start.GetX())
			&& (A.end.GetY() <= end.GetY()) && (end.GetY() <= start.GetY()) && (start.GetY() <= A.start.GetY())
			&& (A.end.GetZ() <= end.GetZ()) && (end.GetZ() <= start.GetZ()) && (start.GetZ() <= A.start.GetZ()))
		{
			//cout << "Multiplicity: [B; A]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return A.start;
		}
		//случай 4
		else if ((A.end.GetX() <= start.GetX()) && (start.GetX() <= end.GetX()) && (end.GetX() <= A.start.GetX())
			&& (A.end.GetY() <= start.GetY()) && (start.GetY() <= end.GetY()) && (end.GetY() <= A.start.GetY())
			&& (A.end.GetZ() <= start.GetZ()) && (start.GetZ() <= end.GetZ()) && (end.GetZ() <= A.start.GetZ()))
		{
			//cout << "Multiplicity: [A; B]" << endl; 
			throw exception("EXCEPTION: Отрезки накладываются друг на друга и имеют бесконечное множество точек пересечения\n"); //return A.start;
		}
		return false;
	}

	/// <summary>
	/// находит точку пересечения, если она одна.
	/// </summary>
	/// <param name="A">другой отрезок</param>
	/// <param name="result"></param>
	/// <returns></returns>
	bool Cross(Segment3D A, Vector3D& result) {
		double U, V, W;
		double q1, q2, s1;
		if ((start.GetX() - end.GetX()) * (A.end.GetY() - A.start.GetY()) - (A.end.GetX() - A.start.GetX()) * (start.GetY() - end.GetY()) != 0) {
			q1 = (A.end.GetX() - end.GetX()) * (A.end.GetY() - A.start.GetY()) - (A.end.GetX() - A.start.GetX()) * (A.end.GetY() - end.GetY());
			q2 = (start.GetX() - end.GetX()) * (A.end.GetY() - A.start.GetY()) - (A.end.GetX() - A.start.GetX()) * (start.GetY() - end.GetY());
			s1 = (start.GetX() - end.GetX()) * (A.end.GetY() - end.GetY()) - (A.end.GetX() - end.GetX()) * (start.GetY() - end.GetY());
			if ((q1 / q2 <= 1) && (s1 / q2 <= 1)) {
				U = q1 / q2 * (start.GetX() - end.GetX()) + end.GetX();
				V = q1 / q2 * (start.GetY() - end.GetY()) + end.GetY();
				W = q1 / q2 * (start.GetZ() - end.GetZ()) + end.GetZ();
				//cout << U << "\t" << V << "\t" << W << endl;
			}
			else return false; // cout << "Don't intersect" << endl;
		}
		else if ((start.GetY() - end.GetY()) * (A.end.GetZ() - A.start.GetZ()) - (A.end.GetY() - A.start.GetY()) * (start.GetZ() - end.GetZ()) != 0) {
			q1 = (A.end.GetY() - end.GetY()) * (A.end.GetZ() - A.start.GetZ()) - (A.end.GetY() - A.start.GetY()) * (A.end.GetZ() - end.GetZ());
			q2 = (start.GetY() - end.GetY()) * (A.end.GetZ() - A.start.GetZ()) - (A.end.GetY() - A.start.GetY()) * (start.GetZ() - end.GetZ());
			s1 = (start.GetY() - end.GetY()) * (A.end.GetZ() - end.GetZ()) - (A.end.GetY() - end.GetY()) * (start.GetZ() - end.GetZ());
			if ((q1 / q2 <= 1) && (s1 / q2 <= 1)) {
				U = q1 / q2 * (start.GetX() - end.GetX()) + end.GetX();
				V = q1 / q2 * (start.GetY() - end.GetY()) + end.GetY();
				W = q1 / q2 * (start.GetZ() - end.GetZ()) + end.GetZ();
				//cout << U << "\t" << V << "\t" << W << endl;
			}
			else return false; // cout << "Don't intersect" << endl;
		}
		else if ((start.GetZ() - end.GetZ()) * (A.end.GetX() - A.start.GetX()) - (A.end.GetZ() - A.start.GetZ()) * (start.GetX() - end.GetX()) != 0) {
			q1 = (A.end.GetZ() - end.GetZ()) * (A.end.GetX() - A.start.GetX()) - (A.end.GetZ() - A.start.GetZ()) * (A.end.GetX() - end.GetX());
			q2 = (start.GetZ() - end.GetZ()) * (A.end.GetX() - A.start.GetX()) - (A.end.GetZ() - A.start.GetZ()) * (start.GetX() - end.GetX());
			s1 = (start.GetZ() - end.GetZ()) * (A.end.GetX() - end.GetX()) - (A.end.GetZ() - end.GetZ()) * (start.GetX() - end.GetX());
			if ((q1 / q2 <= 1) && (s1 / q2 <= 1)) {
				U = q1 / q2 * (start.GetX() - end.GetX()) + end.GetX();
				V = q1 / q2 * (start.GetY() - end.GetY()) + end.GetY();
				W = q1 / q2 * (start.GetZ() - end.GetZ()) + end.GetZ();
				//cout << U << "\t" << V << "\t" << W << endl;
			}
			else return false;// cout << "Don't intersect" << endl;
		}
		else return false;// cout << "Don't intersect" << endl;
		result = Vector3D(U, V, W);
		return true;
	}



public:
	/// <summary>
	/// Конструктор.
	/// Выбрасывает ошибку если start==end.
	/// </summary>
	/// <param name="start">начало отрезка</param>
	/// <param name="end">конец отрезка</param>
	Segment3D(Vector3D start, Vector3D end) {
		if (start != end) {
			this->start = start;
			this->end = end;
		}
		else {
			throw exception("EXCEPTION: Vector3D start==end.\n");
		}
	}
	Vector3D GetStart() {
		return start;
	}
	Vector3D GetEnd() {
		return end;
	}
	/// <summary>
	/// Находит точку пересечения отрезков.
	/// При наложении отрезков выбрасывает exception (бесконечное множество точек).
	/// </summary>
	/// <param name="A">другой отрезок</param>
	/// <param name="result">точка пересечения. При возврате false, значение result не изменяется.</param>
	/// <returns>true - 1 точка пересечения, false - нет точек пересечения</returns>
	bool Intersect(Segment3D A, Vector3D& result) {
		//если в разных плоскостях
		if (!this->Plane(A))
			return false;

		// совпадение одного из концов отрезка с другим
		if (start == A.start || start == A.end) { //пересечение в точке start
			result = start;
			return true;
		}
		else if (end == A.start || end == A.end) { //пересечение в точке end
			result = end;
			return true;
		}

		//если есть наложение кидаем exception, 
		//так как бесконечное множество точек пересечения 
		//(можно выводить границы данного множества, но в ТЗ такого нет)
		Match(A);


		return Cross(A, result);
	}
};






int main() {
	setlocale(LC_ALL, "Russian");
	//start==end
	try {
		Segment3D except = Segment3D(Vector3D(), Vector3D());
		
	}
	catch (exception &ex) {
		cout << ex.what();
	}
	try {
		vector <Vector3D> result = vector<Vector3D>();
		vector <Segment3D> segments = vector <Segment3D>({
			Segment3D(Vector3D(6,0,2),Vector3D(-6,0,2)),Segment3D(Vector3D(0,4,2),Vector3D(0,-4,2)), //0 0 2
			Segment3D(Vector3D(10,0,0),Vector3D(-10,0,0)),Segment3D(Vector3D(0,5,0),Vector3D(0,-5,0)), // 0 0 0 
			Segment3D(Vector3D(0,0,5),Vector3D(0,0,-5)),Segment3D(Vector3D(1,0,0),Vector3D(-1,0,0)),   //0 0 0 отрезки на осях
			Segment3D(Vector3D(1,5,0),Vector3D(5,1,0)),Segment3D(Vector3D(5,5,0),Vector3D(1,1,0)),   //3 3 0
			Segment3D(Vector3D(0,0,5),Vector3D(0,0,-5)),Segment3D(Vector3D(1,0,5),Vector3D(1,0,-5)), //parallel
			Segment3D(Vector3D(-4,-5,6),Vector3D(-6,-1,12)),Segment3D(Vector3D(0,1,-3),Vector3D(1,-1,-6)), // скрещивающиеся
			Segment3D(Vector3D(0,1,5),Vector3D(0,1,-5)),Segment3D(Vector3D(1,5,0),Vector3D(1,-5,0)),		//скрещивающиеся
			Segment3D(Vector3D(0,0,5),Vector3D(0,0,-5)),Segment3D(Vector3D(1,0,0),Vector3D(3,0,0)),			//скрещивающиеся
			Segment3D(Vector3D(0,0,0),Vector3D(5,0,0)),Segment3D(Vector3D(5,0,0),Vector3D(10,0,0)),	 // 5 0 0 совпадающий конец
			Segment3D(Vector3D(0,0,1),Vector3D(0,0,-1)),Segment3D(Vector3D(0,0,-12),Vector3D(0,0,12)), }); // первый отрезок лежит внутри второго (бесконечное множество) exception
		bool intersect;
		for (int i = 0; i < segments.size(); i += 2)
		{
			cout << i / 2 + 1 << "\t";
			result.push_back(Vector3D());
			intersect = segments[i].Intersect(segments[i + 1], result[i / 2]);
			if (intersect)
				cout << result[i / 2].GetX() << "\t" << result[i / 2].GetY() << "\t" << result[i / 2].GetZ() << "\n";
			else
				cout << "Нет точек пересечения\n";
			//Segment3D(Vector3D(1, 1, 1), Vector3D(1, 1, 1));
		}
	}
	catch (exception &ex) {
		cout << ex.what();
	}

}
