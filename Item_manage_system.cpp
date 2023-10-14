#include "list.h"
using namespace std;
ofstream output1("Outbound List.txt",ios::app);
ofstream output2("Inbound List.txt",ios::app);
int main(){
    list itemList;
    outList outboundList;
    inList inboundList;
    itemList.read_list();
    int choice = 1;
    while (choice)
    {
        cout<<"\n| Item Manage Sys |"<<endl;
        cout<<"|1.   Add item    |"<<endl;
        cout<<"|2.   Show item   |"<<endl;
        cout<<"|3.  Search item  |"<<endl;
        cout<<"|4.  Delete item  |"<<endl;
        cout<<"|5. Item outbound |"<<endl;
        cout<<"|6. Item inbound  |"<<endl;
        cout<<"|7. Clear screen  |"<<endl;
        cout<<"|0.   Exit IMS    |"<<endl;
        cout<<"Input choice:";
        cin>>choice;
       switch (choice){
            case 1:
                itemList.add_item();
            break;
            case 2:
                itemList.show_list();
                cout<<"All items shown above,";
                system("pause");
            break;
            case 3:
                do{
                    cout<<"\n1.Search by name\n2.Search by code\nInput choice:";
                    cin>>choice;
                    item itemForSearch;
                    switch (choice){
                        case 1:
                            char name[10];
                            cout<<"Input name to search:";
                            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
                            cin.getline(name,10);
                            itemForSearch.set_item(name,0,"0",0);
                            if (itemList.search(itemForSearch))
                            {
                                itemList.search(itemForSearch)->show_node();
                                system("pause");
                            }
                            else cout<<"Item not found"<<endl;    
                        break;
                        case 2:
                            int c;
                            cout<<"Input code to search:";
                            cin>>c;
                            itemForSearch.set_item("0",c,"0",0);
                            if (itemList.search(itemForSearch))
                            {
                                itemList.search(itemForSearch)->show_node();
                                system("pause");
                            }
                            else cout<<"Item not found"<<endl;
                        break;
                        default:
                        cout<<"Invalid input!"<<endl;
                        choice = 0;
                        break;
                    }
                }while (!choice);
            break;
            case 4:
                do{
                    cout<<"1.Delete by name\n2.Delete by code\nInput choice:";
                    cin>>choice;
                    switch (choice){
                        case 1:
                            {item itemToDelete;char name[10];
                            cout<<"Input name to delete:";
                            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
                            cin.getline(name,10);
                            itemToDelete.set_item(name,0,"0",0);
                            if (itemList.search(itemToDelete))
                            {    
                                if (itemList.search(itemToDelete)->get_data()->quantity != 0 )
                                {
                                    cout<<"Item quantity not 0,invaild delete!"<<endl;
                                    
                                }
                                else{
                                    itemList.search(itemToDelete)->show_node();
                                    itemList.delete_item(itemList.search(itemToDelete));
                                    cout<<"Item deleted";
                                    system("pause");
                                }
                            }
                            else cout<<"Item not found"<<endl;}
                        break;
                        case 2:
                            {int c;item itemToDelete;
                            cout<<"Input code to delete:";
                            cin>>c;
                            itemToDelete.set_item("0",c,"0",0);
                            if (itemList.search(itemToDelete))
                            {    
                                if (itemList.search(itemToDelete)->get_data()->quantity != 0 )
                                {
                                    cout<<"Item quantity not 0,invaild delete!"<<endl;
                                    
                                }
                                else{
                                    itemList.search(itemToDelete)->show_node();
                                    itemList.delete_item(itemList.search(itemToDelete));
                                    cout<<"Item deleted";
                                    system("pause");
                                }
                            }
                            else cout<<"Item not found"<<endl;}
                        break;

                        default:
                            cout<<"Invalid input!"<<endl;
                            choice = 0;
                        break;
                    }
                }while (!choice);
            break;
            case 5:
                do{
                cout<<"1.Outbound by name\n2.Outbound by code\nInput choice:";
                cin>>choice;
                char name[10];int c;item itemForOutbound;
                switch (choice){
                    case 1:
                        cout<<"Input name to outbound:";
                        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
                        cin.getline(name,10);
                        itemForOutbound.set_item(name,0,"0",0);
                        if (itemList.search(itemForOutbound))
                        {
                            itemList.search(itemForOutbound)->show_node();
                            outboundList.out_modify(itemList,itemList.search(itemForOutbound));
                            cout<<"Item after outbound shown below:\n";
                            itemList.search(itemForOutbound)->show_node();
                            system("pause");
                        }
                        else cout<<"Item not found"<<endl;
                        break;
                    case 2:
                        cout<<"Input code to outbound:";
                        cin>>c;
                        itemForOutbound.set_item("0",c,"0",0);
                        if (itemList.search(itemForOutbound))
                        {
                            itemList.search(itemForOutbound)->show_node();
                            outboundList.out_modify(itemList,itemList.search(itemForOutbound));
                            cout<<"Item after outbound shown below:\n";
                            itemList.search(itemForOutbound)->show_node();
                            system("pause");
                        }
                        else cout<<"Item not found"<<endl;
                        break;
                    default:
                    cout<<"Invalid input!"<<endl;
                    choice = 0;
                    break;
                }
            }while (!choice);
            break;
            case 6:
                do{
                cout<<"1.Inbound by name\n2.Inbound by code\nInput choice:";
                cin>>choice;
                char name[10];int c;item itemForInbound;
                switch (choice){
                    case 1:
                        cout<<"Input name to inbound:";
                        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
                        cin.getline(name,10);
                        itemForInbound.set_item(name,0,"0",0);
                        if (itemList.search(itemForInbound))
                        {
                            itemList.search(itemForInbound)->show_node();
                            inboundList.in_modify(itemList,itemList.search(itemForInbound));
                            cout<<"Item after Intbound shown below:\n";
                            itemList.search(itemForInbound)->show_node();
                            system("pause");
                        }
                        else cout<<"Item not found"<<endl;
                    break;
                    case 2:
                        cout<<"Input code to search:";
                        cin>>c;
                        itemForInbound.set_item("0",c,"0",0);
                        if (itemList.search(itemForInbound))
                        {
                            itemList.search(itemForInbound)->show_node();
                            inboundList.in_modify(itemList,itemList.search(itemForInbound));
                            cout<<"Item after Inbound shown below:\n";
                            itemList.search(itemForInbound)->show_node();
                            system("pause");
                        }
                        else cout<<"Item not found"<<endl;
                    break;
                    default:
                    cout<<"Invalid input!"<<endl;
                    choice = 0;
                    break;
                }
            }while (!choice);
            break;
            case 7:
                
                
            break;
            case 0:
                cout<<"Are you sure to exit?Input choice(Y:0/n:else):";
                cin>>choice;
            break;
            default:
                cout<<"Invalid input!"<<endl;
            break;
       }
       

    }
    itemList.save_list();
    {
    
    outboundList.output_outbound_txt();

    inboundList.output_inbound_txt();
    output1.close();
    output2.close();

    }
    return 0;
}







