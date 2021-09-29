#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

struct node
{
	string info;
	int indx;
	node* parent;
	string code;

	vector<node*>children;


};

class catalog //Main Tree structure
{	
	private:
	node* root;

	public:
	node* addChild(node *parent,string info);
	node *createRoot();
	node *nextNode(node*parent,int indx);
	void removeNode(node*parent, int indx);
	void printChildNodes(node*parent);
	void findPath(string code);
	
};



node* catalog::addChild(node *parent,string info) //Add sections/Books
{	
	int ind=0;
	int n=(parent->children).size();
	if(n==0)ind=0;
	else{ind=(parent->children)[n-1]->indx+1;}

	ostringstream str;
	str<<(ind+1);

	node *temp=new node;
	temp->indx=ind;
	temp->info=info;
	temp->code=(parent->code)+"."+str.str();
	temp->parent=parent;
	(parent->children).push_back(temp);
	return temp;
}

node* catalog::createRoot() //Initate tree
{
	root=new node;
	root->info="catalog";
	root->code="";
	root->indx=0;
	root->parent=NULL;
	return root;
}

void catalog::removeNode(node*parent,int indx) //Delete Section/Book
{	
	if(indx<(parent->children).size())
	{
	vector<node*>::iterator start;
	start=(parent->children).begin();
	(parent->children).erase(start+indx);
	}
	else{cout<<"\n!!Section/Book No.out of bounds!!\n";}

}

void catalog::findPath(string code) //Prints the path to book through sections
{
	node*parent=root;
	vector<string>path;
	vector<int>tokens;  

    stringstream check1(code);  
    string intermediate; 
    int token=0;
    while(getline(check1, intermediate, '.')) 
    { 	
    	stringstream temp(intermediate);
    	temp>>token;
        tokens.push_back(token-1); 
    } 

	while(tokens.size()!=0)
	{	
		int token=tokens[0];
		tokens.erase(tokens.begin());

		int found=0;
		for(int i=0;i<(parent->children).size();i++)
		{	
			if(token==((parent->children)[i]->indx))
			{	
				path.push_back((parent->children)[i]->info);
				parent=(parent->children)[i];
				found=1;
				break;
			}

		}
		if(!found){cout<<"\n!! Section/Book path not found!!\n";return;}

	}

	for(int i=0;i<path.size()-1;i++)cout<<path[i]<<"->";
	cout<<path[path.size()-1]<<endl;

}

node* catalog::nextNode(node*parent,int indx) //Navigate based on user input
{	
	int num_sections=parent->children.size();
	if(indx==num_sections) //Adding section
	{
		string info;
		cout<<"enter Section name: ";
		cin.ignore();
		getline(cin,info);
		return addChild(parent,info)->parent;
	}
	if(indx==num_sections+1) //Removing section
	{	
		int input;
		cout<<"enter Section No. to delete: ";
		cin>>input;
		removeNode(parent,input-1);
		return parent;
	}
	if(indx==num_sections+2) //Navigating back
	{
		if(parent->parent==NULL)return parent;
		else return parent->parent;
	}
	if(indx==num_sections+3) //Path Finding
	{	
		string code;
		cout<<"enter Book code: ";
		cin>>code;
		findPath(code);
		return parent;	
	}

	if(indx>num_sections||indx<0){cout<<"\n !!Section No. out of bounds!!\n";return parent;} //Navigating to a section
	return parent->children[indx];
}




void catalog::printChildNodes(node* parent) //Print Sections/Books
{	
	int i=0;
	for(;i<(parent->children).size();i++)
	{
		string info=(parent->children[i])->info;
		string code=((parent->children[i])->code);
		cout<<i+1<<"."<<info<<" ("<<code.erase(0,1)<<")"<<endl;
	}
	cout<<i+1<<".Create Section"<<endl;
	cout<<i+2<<".Remove section"<<endl;
	cout<<i+3<<".Navigate back"<<endl;
	cout<<i+4<<".Find Shelf"<<endl;
}


int main()
{
	catalog tree;

	node*root=tree.createRoot();
	node*curNode=root;


	int ext=0;
	while(!ext)
	{	
		cout<<"\n****"<<(curNode->info)<<"****"<<endl;
		int input;
		cout<<"Choose from following. Press '0' to exit:\n";
		tree.printChildNodes(curNode);
		cin>>input;
		if(input==0)break;
		curNode=tree.nextNode(curNode,input-1);
		
		if(curNode==NULL){cout<<"exit";ext=1;}



	}




}















































































