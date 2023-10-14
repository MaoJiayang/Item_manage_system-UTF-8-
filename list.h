#include "item.h"
using namespace std;
class node//one item one node
{
private:
    item *pData;//point to the item
    node *pNext;//point to next item node
public:
    node(){ pData = new item;pNext = NULL;}//constructor
    node(node &node){//copy constructor
        pData = node.pData;
        pNext = node.pNext;
    }
    void input_data(item *pInput){pData = pInput;}//put item into node
    void show_node(){pData->show();}//show the item data in this node
    int get_id(){return pData->get_item_code();}
    item *get_data(){return pData;}//get data from node(return a pointer)
    node *get_previous_node(node *);

    friend class list;
    friend class outList;
    friend class inList;

};
class list
{
public:
    node *pHead;//head pointer
    node *p1;
    node *p2;
    list(){pHead = new node;p1 = pHead;p2 = pHead;pHead->pNext = NULL;}//default constructor,create a head node
    ~list(){delete_list();}//destructor
    node *search(item &itemToSearch);//search for a certain node and return its pointer. return 0 if not found
    void delete_item(node *);//delete a node and return its pointer
    void show_list();//print the list
    void delete_list();//delete whole list
    void insert(node *insertPosition,node *nodeToInsert);
    void read_list();//read list form hard disk
    void save_list();//save list to hard disk

    void add_item();//add an item to the right place in the list
};
class outList:public list
{
public:
    void out_modify(list& itemList,node* nodeToModify);
    void output_outbound_txt();
};
class inList:public list
{
public:
    void in_modify(list& itemList,node* nodeToModify);
    void output_inbound_txt();
};
float item::print_outbound_item(){
    extern ofstream output1;
    int i = 0;float sumOfPrice = 0;
    output1<<"\n-------------------------\nItem name:"<<itemName<<"\t\tItem code:"<<itemCode<<"\tItem colour:"<<colour<<"\t\tItem quantity:"<<quantity<<"\t Num of Brands:"<<brandNumber<<"\n\n";
    for ( i = 0; i < brandNumber; i++)
    {
        output1<<"Brand"<<i+1<<"-> |Name:"<<brands[i].brandName<<"\t|Brand code:"<<brands[i].brandCode<<"\t|Brand quantity:"<<brands[i].quantity<<"\t|Brand price:"<<brands[i].brandPrice<<endl;
        sumOfPrice += brands[i].brandPrice*brands[i].quantity;
    }
    return sumOfPrice;
}
float item::print_inbound_item(){
    extern ofstream output2;
    int i = 0;float sumOfPrice = 0;
    output2<<"\n-------------------------\nItem name:"<<itemName<<"\t\tItem code:"<<itemCode<<"\tItem colour:"<<colour<<"\t\tItem quantity:"<<quantity<<"\t Num of Brands:"<<brandNumber<<"\n\n";
    for ( i = 0; i < brandNumber; i++)
    {
        output2<<"Brand"<<i+1<<"-> |Name:"<<brands[i].brandName<<"\t|Brand code:"<<brands[i].brandCode<<"\t|Brand quantity:"<<brands[i].quantity<<"\t|Brand price:"<<brands[i].brandPrice<<endl;
        sumOfPrice += brands[i].brandPrice*brands[i].quantity;
    }
    return sumOfPrice;
}    
void outList::out_modify(list& itemList,node* nodeToModify){
    int brandNo = 0,outboundQuantity = 0;
    cout<<"All brands shown above,input brand number to outbound"<<endl;
    cin>>brandNo;
    if (brandNo <= nodeToModify->get_data()->get_brandNumber() && brandNo > 0)//if brandNo is in the item
    {
        cout<<"Input outbound quantity:"<<endl;
        cin>>outboundQuantity;
        if (outboundQuantity > 0 && outboundQuantity <= nodeToModify->get_data()->get_brands()[brandNo-1].quantity)//if there's enough quantity
        {   
            item temp = *nodeToModify->get_data();
            if ( this->p1 = this->search(temp) ){//if there's already a same item in the outboundlist       
                this->p1->get_data()->get_brands()[brandNo-1].quantity += outboundQuantity;
                this->p1->get_data()->maintenance(); 
            } 
            else {
                p1 = new node;
                *p1->get_data() = temp; 
                this->p1->get_data()->set_zero();//put 0 to all brands' quantity,for it's an new outbound
                this->p1->get_data()->get_brands()[brandNo-1].quantity = outboundQuantity;
                this->p1->get_data()->maintenance();
                insert(pHead,p1);
            }
            nodeToModify->get_data()->get_brands()[brandNo-1].quantity -= outboundQuantity;
            nodeToModify->get_data()->maintenance(); //maintain the right sum of quantities in item.
        }
        else cout<<"Not enough quantity for outbound!"<<endl;
        
    }
    else cout<<"brand not exist!"<<endl; 
}
void outList::output_outbound_txt(){
    extern ofstream output1;
    float sumOfPrice = 0;
    if (pHead->pNext == NULL)
    {
        return;
    }
    timer = time(NULL);
    output1<<"\n"<<ctime(&timer)<<"Outbound record:----------------------------------------------------------------------------------------";
    p2 = pHead->pNext;
    while (p2->pNext != NULL)
    {
        sumOfPrice += p2->get_data()->print_outbound_item();
        p2 = p2->pNext;
    }
    sumOfPrice += p2->get_data()->print_outbound_item();
    output1<<"Price sum of outbound cargo:"<<sumOfPrice<<"--------------------------------------------------------------------------------------------------------"<<endl; 
}
void inList::in_modify(list& itemList,node* nodeToModify){
    int brandNo = 0,inboundQuantity = 0;
    cout<<"All brands shown above,input brand number to inbound,input next one to create a new brand"<<endl;
    cin>>brandNo;
    if (brandNo == nodeToModify->get_data()->get_brandNumber()+1 && brandNo > 0 && brandNo < MAXNUM){//if brandNo is the next NO. to the exsistd brand,add a new one
        cout<<"inbound a new band:\n";
        cout<<"input brand "<<brandNo<<" name,no more than 20 char."<<endl;char name[10];
        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
        cin.getline(name,sizeof(name)+1);
        cout<<"input brand "<<brandNo<<" code"<<endl;int code;
        cin>>code;
        cout<<"input brand "<<brandNo<<" price"<<endl;float price;
        cin>>price;
        nodeToModify->get_data()->get_brands()[brandNo-1].set_brand(name,code,price);
        nodeToModify->get_data()->maintenance();
    }
    else if(brandNo > nodeToModify->get_data()->get_brandNumber()+1){
        cout<<"Invalid inbound or brand number exceed max number.\n";return;
    }
    //after all above, brand number is in the brand,change its quantity
    if (brandNo <= nodeToModify->get_data()->get_brandNumber() && brandNo > 0)//if brandNo is in the item
    {
        cout<<"Input inbound quantity:"<<endl;
        cin>>inboundQuantity;
        
        {   
            item temp = *nodeToModify->get_data();
            if ( this->p1 = this->search(temp) ){//if there's already a same item in the inboundlist      
                this->p1->get_data()->get_brands()[brandNo-1].quantity += inboundQuantity;
                this->p1->get_data()->maintenance(); 
            } 
            else {
                p1 = new node;
                *p1->get_data() = temp ; 
                this->p1->get_data()->set_zero();//put 0 to all brands' quantity,for it's an new inbound
                this->p1->get_data()->get_brands()[brandNo-1].quantity = inboundQuantity;
                this->p1->get_data()->maintenance();
                insert(pHead,p1);
            }
            nodeToModify->get_data()->get_brands()[brandNo-1].quantity = nodeToModify->get_data()->get_brands()[brandNo-1].quantity + inboundQuantity;
            nodeToModify->get_data()->maintenance(); //maintain the right sum of quantities in item.
        }
    }
    else cout<<"invalid input!"<<endl;
    
}
void inList::output_inbound_txt(){
    extern ofstream output2;
    float sumOfPrice = 0;
    if (pHead->pNext == NULL)
    {
        return;
    }
    timer = time(NULL);
    output2<<"\n"<<ctime(&timer)<<"Inbound record:----------------------------------------------------------------------------------------";
    p2 = pHead->pNext;
    while (p2->pNext != NULL)
    {
        sumOfPrice += p2->get_data()->print_inbound_item();
        p2 = p2->pNext;
    }
    sumOfPrice += p2->get_data()->print_inbound_item();
    output2<<"Price sum of inbound cargo:"<<sumOfPrice<<"--------------------------------------------------------------------------------------------------------"<<endl;
}
node* node::get_previous_node(node *h){
    node *p3;
    p3 = h;
    while (p3->pNext != this)
    {
        p3 = p3->pNext;
    }
    return p3;
}
void list::delete_item(node *nodeToDelete ){//delete a node and return its pointer
    if (nodeToDelete->pNext == NULL)
    {
        p2 = nodeToDelete->get_previous_node(pHead);
        delete nodeToDelete;
        p2->pNext = NULL;
    }
    else{
        p2 = nodeToDelete->get_previous_node(pHead);
        p2->pNext = nodeToDelete->pNext;
        delete nodeToDelete;
    } 
}
node* list::search(item &itemToSearch){//search for a certain node and return its pointer. return 0 if not found
    p1 = pHead->pNext;
	if(itemToSearch.get_item_code() == 0)
	{
		while(p1)
		{
			if(p1->pData->compare_name(itemToSearch))
			return p1;//search by name
			p1=p1->pNext;
		}
	}
	else
	{
		while(p1)
		{
			if(p1->pData->compare_code(itemToSearch))
			return p1;//search by code
			p1 = p1->pNext;
		}
	}
	return 0;
}
void list::show_list(){//print the list
    if (pHead->pNext == NULL)
    {
        cout<<"item list is empty!";
        return;
    }
    p2 = pHead->pNext;
    while (p2->pNext != NULL)
    {
        p2->show_node();
        p2 = p2->pNext;
    }
    p2->show_node();
   
}
void list::delete_list(){//delete whole list
    if (pHead->pNext == NULL)
    {
        return;
    }
    p2 = pHead->pNext;
    while (p2->pNext != NULL)
    {
        delete pHead;
        pHead = p2;
        p2 = p2->pNext;
    }
    delete p2;
}
void list::insert(node *insertPosition,node *nodeToInsert){//insert a node after the insert position

        nodeToInsert->pNext = insertPosition->pNext;
        insertPosition->pNext = nodeToInsert;
    
}
void list::add_item(){//add an item to the right place in the list
    p1 = new node;
    
    item *inputItem;inputItem = new item;//a temporary item for input
    cout<<"Input item name"<<endl;char name[10];
    cin.ignore(numeric_limits <streamsize> ::max(), '\n');//all getline after one cin use need this 
    cin.getline(name,sizeof(name)+1);
    cout<<"Input item code"<<endl;int code;
    cin>>code;
    cout<<"Input item colour"<<endl;char color[10];
    cin.ignore(numeric_limits <streamsize> ::max(), '\n');
    cin.getline(color,sizeof(color)+1);
    cout<<"Input brand number,no more than max"<<endl;int number;
    cin>>number;
    while (number > MAXNUM)
    {
        cout<<"brand number exceed max"<<endl;
        cout<<"Input brand number,no more than max"<<endl;
        cin>>number;
    }
    

    inputItem->set_item(name,code,color,number);//can I replace it with p1 instead?
    inputItem->set_brands_in_item(number);
    p1->input_data(inputItem);
    node *p3 = pHead;p2 = pHead;
    if (p2->pNext == NULL)//if list is empty(p2 is pointed to first node,if pData of first node is NULL,that means empty list)
        {insert(pHead,p1);return;}
    else{
        p2 = pHead->pNext;//put p2 to the head
        while ( p2->get_id() < code )//search for position for new node by ascend order then insert it into the right position
        {       
            p3 = p2;
            p2 = p2->pNext;//do until the node bigger than p1 is found
            if (p2 == NULL){//if point to the tail of the list
                p3->pNext = p1;p1->pNext = NULL;return;
           } 
        }
        insert(p3,p1);
    }
}
void list::read_list(){//read list form hard disk
    fstream readList( "list.dat", ios_base::in |ios_base::binary);
    if (!readList)
    {
        cout<<"unable to open input file!No list has been saved yet,please save a list first."<<endl;
        return;
    }
    item temp;
    while ( !readList.eof() )//if file not end.attention! eof()will read 2 chars rather than 1 at the eof!(1 for last char and 1 for eof)
    {
        if (pHead->pNext == NULL)//if list is empty
        {
            p1 = new node;
            readList.read((char * )(&temp),sizeof(item));
            *p1->pData = temp;
            pHead->pNext = p1;  
        }
        else{
            p1 = new node;		
            readList.read((char * )(&temp),sizeof(item));
            *p1->pData = temp;
            p2 = p2->pNext ;
            p2->pNext = p1;
        }
    }
    delete p1;
    p1 = pHead;
    p2->pNext = NULL;
    readList.close();
    cout<<"Load complete!"<<endl;
}
void list::save_list(){//save list to hard disk
    p1 = pHead->pNext;
    fstream saveList( "list.dat", ios_base::out | ios_base::trunc |ios_base::binary);
    if (!saveList)
    {
        cout<<"unable to open output file!";
        return;
    }
    if (p1 == NULL)
    {
        cout<<"list not exist!"<<endl;
        return;
    } 
    while (p1->pNext != NULL)
    {
        saveList.write((const char*)(p1->pData),sizeof(item));
        p1 = p1->pNext;
    }
    saveList.write((const char*)(p1->pData),sizeof(item));
    saveList.close();
    cout<<"list saved"<<endl;
}