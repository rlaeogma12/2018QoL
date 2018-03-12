/*
 * calculator.cpp
 *
 * Copyright 2018  <daeheum@daeheum-FX503VD>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <iostream>
using namespace std;

class Calculator{
private:
	char *input;
public:
	void setInput(char *string);
	double add(double x, double y);
	double sub(double x, double y);
	double mul(double x, double y);
	double div(double x, double y);
	double totalResult();
};

void initCalculator(){
	Calculator QoLCalculator();
	int val;

	bool power = true;
	while(power){
			cout<<"Write the input(exit:0)"<<endl;
			cout<<":";
			cin>>val;

			if(val==0){
					power = false;
			}
	}
}

int main()
{
	initCalculator();

	return 0;
}
