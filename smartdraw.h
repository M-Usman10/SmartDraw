/*
 * smartdraw.h
 *
 *  Created on: Apr 22, 2017
 *  Author: M.Usman
 */
#ifndef SMARTDRAW_H_
#define SMARTDRAW_H_
#include <cmath>
#include <utility>
#include "util.h"
#include <list>
#include <string>
#include <fstream>
using namespace std;
template<class T, class T2>
class my_pair
{
public:
	T first;
	T2 second;
	my_pair(T f, T2 s)
	{
		first = f;
		second = s;
	}
	bool operator==(const my_pair<T, T2> & p) const
	{
		return first == p.first && second==p.second;
	}
};

template<typename T>
class List: public list<T>
{
public:
	T & operator[](const int & i)
	{
		auto it = this->begin();
		advance(it, i);
		return (*it);
	}
};
class Vertex
{
public:
	int x, y;
	Vertex(int x1 = 0, int y1 = 0) :
			x(x1), y(y1)
	{

	}
	void save(ofstream & ofile,const char * path)
	{
		ofile.write((char *) &x, sizeof(int));
		ofile.write((char *) &y, sizeof(int));
	}
	void load(ifstream & ifile,const char * path)
		{
			ifile.read((char *) &x, sizeof(int));
			ifile.read((char *) &y, sizeof(int));
		}
};
class Edge
{
public:
	int V1;
	int V2;
	Edge()
	{
		V1 = 0;
		V2 = 0;
	}
	Edge(int v1, int v2) :
			V1(v1), V2(v2)
	{

	}
	void load(ifstream & ifile,const char * path)
	{
		ifile.read((char *) &V1, sizeof(int));
		ifile.read((char *) &V2, sizeof(int));
	}
	void save(ofstream & ofile,const char * path)
	{
		ofile.write((char *) &V1, sizeof(int));
		ofile.write((char *) &V2, sizeof(int));
	}
};
class Shape
{
public:
	int no_of_edges;
	int no_of_vertices;
	List<Vertex> vertices;
	List<Edge> edges;
	Shape(int v_size/* #vertices */, int e_size/* #edges*/, List<Vertex> & v,
			List<Edge> & e)
	{
		no_of_edges = e_size;
		no_of_vertices = v_size;
		vertices = v;
		edges = e;
	}
	Shape()
	{
		no_of_edges = 0;
		no_of_vertices = 0;
	}
	void AddVertex(int x, int y)
	{
		cout<<"Added"<<endl;
		++no_of_vertices;
		Vertex V(x, y);
		vertices.push_back(V);
	}
	void AddVertex(Vertex & V)
	{
		cout<<"Added"<<endl;
		cout<<"Vertices are "<<no_of_vertices<<endl;
		++no_of_vertices;
		vertices.push_back(V);
	}
	void AddEdge(Edge & E)
	{
		cout<<"Added Edge"<<endl;
		++no_of_edges;
		edges.push_back(E);
	}
	void ChangeVertices(List<Vertex> V)
	{
		vertices = V;
		no_of_vertices = V.size();
	}
	void ChangeEdges(List<Edge> E)
	{
		edges = E;
		no_of_edges = E.size();
	}
	void display()
	{
		int size=vertices.size();
		cout<<"Vertices "<<size<<endl;
		for (int i = 0; i < no_of_vertices; ++i)
		{
			DrawCircle(vertices[i].x, vertices[i].y, 2, colors[RED]);
		}
		for (int i = 0; i < no_of_edges; ++i)
		{
             DrawLine(vertices[edges[i].V1].x,vertices[edges[i].V1].y,vertices[edges[i].V2].x,vertices[edges[i].V2].y,5,colors[RED]);
		}
	}
	void save(ofstream & ofile,const char * path)
	{
		ofile.write((char *) &no_of_vertices, sizeof(int));
		for (int i = 0; i < no_of_vertices; ++i)
		{
			vertices[i].save(ofile,path);
		}
		ofile.write((char *) &no_of_edges, sizeof(int));
		for (int i = 0; i < no_of_edges; ++i)
		{
			edges[i].save(ofile,path);
		}
	}
	void load(ifstream & ifile,const char * path)
	{

		ifile.read((char *) &no_of_vertices, sizeof(int));
		for (int i = 0; i < no_of_vertices; ++i)
		{
			Vertex v;
			vertices.push_back(v);
			vertices[i].load(ifile,path);
		}
		ifile.read((char *) &no_of_edges, sizeof(int));
		for (int i = 0; i < no_of_edges; ++i)
		{
			Edge E;
			edges.push_back(E);
			edges[i].load(ifile,path);
		}

	}
};
class rectangle:public Shape
{

};
void writecode(List<Shape> & );
void readcode(List<Shape> & );
void switchmode(int , int & ,bool &);
double l2_distance(int ,int ,int,int);
my_pair<int,int> get_least_dis(int ,int ,List<Shape> &);
void draw(int, int, int, int, List<Shape> &);
#endif /* SMARTDRAW_H_ */
