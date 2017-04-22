#include "smartdraw.h"
void switchmode(int x, int & mode,bool & first_time)
{
	if (x >= 200 and x <= 308)
		mode = 0;
	else if (x >= 350 && x <= 425)
		mode = 1;
	else if (x >= 465 && x <= 530)
		mode = 2;
	else if (x >= 594 && x <= 630)
		{
		  first_time=true;
		  mode = 3;
		}

}
double l2_distance(int x1, int y1, int x2, int y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
my_pair<int,int> get_least_dis(int x, int y, List<Shape> & shapes)
{
	if(!shapes.size())
	{
		my_pair<int,int> least(-1,-1);
		return least;
	}
	my_pair<int,int> least(0,0);
	for (int i = 0; i < shapes.size(); ++i)
	{
		int max = shapes[i].vertices.size();
		for (int j = 0; j < max; ++j)
		{
            if(l2_distance(shapes[i].vertices[j].x,shapes[i].vertices[j].y,x,y) < l2_distance(shapes[least.first].vertices[least.second].x,shapes[least.first].vertices[least.second].y,x,y))
            {
            	least.first=i;
            	least.second=j;

            }
		}
		return least;
	}

}
void draw(int mode, int x, int y, int index, List<Shape> & shapes)
{
	if (mode == 2)
	{
		Vertex V(x, y);
		shapes[index].AddVertex(V);
	}

}
void readcode(List<Shape> & s)
{
	string path;
	cout << "Write the name of your new file" << endl;
	cin >> path;
	ifstream ifile(path.c_str(),ios::binary);
	int size=0;
	ifile.read((char *) &size,sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		Shape sh;
		s.push_back(sh);
		s[i].load(ifile,path.c_str());
	}
}
void writecode(List<Shape> & s)
{

	cout<<"Press c To Cancel";
	char ch;
	cin>>ch;
	if(ch=='c')
		return;
	string path;
	cout << "Write the name of your new file" << endl;
	cin >> path;
	ofstream ofile(path.c_str());
	int size=s.size();
	ofile.write((char *) &size,sizeof(int));
	for (int i = 0; i < s.size(); ++i)
	{
		s[i].save(ofile,path.c_str());
	}
	ofile.close();
}
