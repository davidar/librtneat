/*
 * Copyright (C) The University of Texas, 2006. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT
 * AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE
 * ARISE FROM COURSE OF DEALING OR USAGE OF TRADE. NO WARRANTY IS EITHER
 * EXPRESS OR IMPLIED WITH RESPECT TO THE USE OF THE SOFTWARE OR
 * DOCUMENTATION. Under no circumstances shall University be liable for
 * incidental, special, indirect, direct or consequential damages or loss
 * of profits, interruption of business, or related expenses which may
 * arise from use of Software or Documentation, including but not limited
 * to those resulting from defects in Software and/or Documentation, or
 * loss or inaccuracy of data of any kind.
 */

// Modifications made by David Roberts <d@vidr.cc>, 2010.

#include "innovation.h"

using namespace NEAT;

Innovation::Innovation(int nin,int nout,double num1,double num2,int newid,double oldinnov) {
	innovation_type=NEWNODE;
	node_in_id=nin;
	node_out_id=nout;
	innovation_num1=num1;
	innovation_num2=num2;
	newnode_id=newid;
	old_innov_num=oldinnov;

	//Unused parameters set to zero
	new_weight=0;
	new_traitnum=0;
	recur_flag=false;
}

Innovation::Innovation(int nin,int nout,double num1,double w,int t) {
	innovation_type=NEWLINK;
	node_in_id=nin;
	node_out_id=nout;
	innovation_num1=num1;
	new_weight=w;
	new_traitnum=t;

	//Unused parameters set to zero
	innovation_num2=0;
	newnode_id=0;
	recur_flag=false;
}

Innovation::Innovation(int nin,int nout,double num1,double w,int t,bool recur) {
	innovation_type=NEWLINK;
	node_in_id=nin;
	node_out_id=nout;
	innovation_num1=num1;
	new_weight=w;
	new_traitnum=t;

	//Unused parameters set to zero
	innovation_num2=0;
	newnode_id=0;
	recur_flag=recur;
}
