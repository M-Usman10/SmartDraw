#include "smartdraw.h"
void writecode(List<Shape> & s)
{

	string path;
	cout << "Write the name of your new file" << endl;
	cin >> path;
	ofstream ofile(path.c_str());
	for (int i = 0; i < s.size(); ++i)
	{
        s[i].save(path.c_str());
	}
	ofile.close();
}
void switchmode(int x, int & mode)
{
	if (x >= 200 and x <= 308)
		mode = 0;
	else if (x >= 350 && x <= 425)
		mode = 1;
	else if (x >= 465 && x <= 530)
		mode = 2;
	else if (x >= 594 && x <= 630)
		mode = 3;

}
void draw(int mode, int index, int x, int y, List<Shape> & shapes)
{
	if (mode == 2)
	{
		Vertex V(x, y);
		shapes[index].AddVertex(V);
	}
	else if (mode == 3)
	{
		Edge E;
	}
}
