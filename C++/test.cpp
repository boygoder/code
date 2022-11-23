#include <vector>
#include <iostream>
#include "math.h"
using namespace std;

vector<double> RGBToLAB(vector<int>& r)
{
	double L = 0.3811 * r[0] + 0.5783 * r[1] + 0.0402 * r[2];
	double M = 0.1967 * r[0] + 0.7244 * r[1] + 0.0782 * r[2];
	double S = 0.0241 * r[0] + 0.1288 * r[1] + 0.8444 * r[2];
	double Ls = log10(L), Ms = log10(M), Ss = log10(S);
	double l = (Ls + Ms + Ss) / sqrt(3);
	double alpha = (Ls + Ms - 2 * Ss) / sqrt(6);
	double beta = (Ls - Ms) / sqrt(2);
	vector<double> res = {l,alpha,beta};
	return res;
}
vector<int> LABToRGB(vector<double>& l)
{
	double ls = l[0] / sqrt(3);
	double alphas = l[1] / sqrt(6);
	double betas = l[2] / sqrt(2);
	double L = pow(10, ls + alphas + betas);
	double M = pow(10, ls + alphas - betas);
	double S = pow(10, ls - 2 * alphas);
	int R = 4.4679 * L - 3.5873 * M + 0.1193 * S;
	int G = -1.2186 * L + 2.3809 * M - 0.1624 * S;
	int B = 0.0497 * L - 0.2439 * M + 1.2045 * S;
	vector<int> res = {R, G, B};
	return res;
};
int main()
{
	vector<int> RGBcolor = {255,255,255};
	vector<double> LABcolor = RGBToLAB(RGBcolor);
	vector<double> AveragePhotograph = {3.415237,0.021764,0.012870};
	vector<double> AverageSource = {3.749743,-0.001437,-0.001167};
	vector<double> SDPhotograph = {0.408779,0.045302,0.013204};
	vector<double> SDSource = {0.202977,0.023172,0.004098};
	for(int i = 0; i < 3; i++)
	{
		LABcolor[i] = (LABcolor[i] - AverageSource[i])*SDPhotograph[i]/SDSource[i] + AveragePhotograph[i];
	}
	vector<int> res = LABToRGB(LABcolor);
	for(int& a : res)
	{
		cout << a <<" ";
	}
	cout << endl;
	return 0;
}
