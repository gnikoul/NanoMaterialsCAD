#pragma once

#include "stdafx.h"

////////////////////////////////
//helping classes
class Group
{
public:
	Group() {};
	void _Group(int N_a, int N_t) { N_atoms = N_a; _N_types = N_t; _reserve(N_a); };/*(number_of_atoms, number_of_types)*/
	~Group() {};

	unsigned int N_atoms;//number of atoms
	std::vector<unsigned int> N_atoms_per_type;//number of atoms
	std::vector<jgn::vec3> color_per_type;//color of atoms
	jgn::vec3 primitiveVec[3];//the primitiveVec
	jgn::vec3 primitiveBase[3];//the primitiveVec/|primitiveVec|
	std::vector<jgn::vec3> position;
	std::vector<jgn::string> type;
	int _N_types;
	std::vector<jgn::string> _alltype;
	std::vector<jgn::string> selective_dynamics;
	std::vector<jgn::vec3> color;
	std::vector<float> number;//atomic number
	std::vector<float> weight;//atomic weight
	std::vector<float> radius;
	std::vector<bool> isSelected;
	std::vector<bool> isdeleted;
	std::vector<bool> ishovered;
	std::vector<bool> iscut;//if the atoms is cut by a surface

	void _reserve(const unsigned int N_a);
	void N_types(const unsigned int N_t);
};


class VSystem
{
public:

	VSystem();
	~VSystem();

	int N_types = 0;//#N of different elements
	std::vector<jgn::string> types;//#N of different elements
	int N_atoms = 0;// total #N of the system
	std::vector<int> N_atoms_per_type;
	std::vector<jgn::vec3> color_per_type;//color of atoms
	jgn::vec2 hoveredatom = jgn::vec2(-1, -1);// group,atoms of the atom that is currently hovered
	jgn::vec2 hoveredatom_prev = jgn::vec2(-1, -1);
	float simulationboxVolume;


	int N_groups = 0;//#N of groups
	int _isimulationBox = 0;
	jgn::vec3 simulationBoxEdges[8];//the simumation box 2 draw;
	std::vector<jgn::vec3> _sellectHistory;//(group,atom,history)
	int _sellectHistory2undo = 1;//


	std::vector<Group> group;
	std::vector<int> deletedHistory;

	void draw();
	void cut();
	void _drawSimulationBox();
	void _updateSimulationBox();
	void setSimulationBox(int s);
	void _drawBase();
	void _drawDistanceToolLine();
	void _drawatoms();
	void _drawsysteminfo();
	void unsellectAll();
	void undoSellect();
	void selected_change_element(std::string elem);
	jgn::vec2 _hoveringAnatom(const jgn::vec2 m);
	class Grouplist
	{
	public:
		bool hovering_prev = false;
		bool hovering = false;
		bool open = false;//if the list is showing
		void draw();
		bool checkhoverstatus(const jgn::vec2 m);// the input is the mouse
		class Options
		{
		public:
			int hovering_prev = -1;
			int hovering = -1;
			bool checkhoverstatus(const jgn::vec2 m);// the input is the mouse
		} options;
	} grouplist;
}EXT vs;



