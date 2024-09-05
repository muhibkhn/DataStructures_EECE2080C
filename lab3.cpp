#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

using namespace std;
#define MAX_ITEMS 30
double opp = 0;


template <class T>
class OrderedList
{
protected:
  T *items[MAX_ITEMS];
  int items_list = 0;

public:
  OrderedList(){
    for (int i = 0; i < MAX_ITEMS; i++){
      items[i] = nullptr;}}
  
  void AddItem(T elem){ 
    for (int i = 0; i < MAX_ITEMS; i++){
      if (items[i] == nullptr){
        items[i] = new T;
        *items[i] = elem;
        items_list++;
        opp++;
        break;}
      
      else if (elem < *items[i]){
        opp++;
        try{
          for (int j = items_list; j > i; j--){
            if (j == MAX_ITEMS){
              opp++;
              throw out_of_range("ERROR: The Array is full.");}
            else{
              items[j] = new T;
              *items[j] = *items[j - 1];
              opp++;}
          }
          *items[i] = elem;
          items_list++;
          break;}
        catch (out_of_range msg)
        {
          cout << msg.what();
          break;}}}}
  void RemoveItem(T elem){
    int position = -1;
    for (int i = 0; i < items_list; i++){
      if (elem == *items[i]){
        position = i;
        break;}
      opp++;}
    try{
      if (position == -1){
        __throw_out_of_range("ERROR: items that to be removed doesn't exist!");
      }
      int i = position;
      for (; i < items_list - 1; i++){
        *items[i] = *items[i + 1];
        opp++;}
      items[i] = nullptr;
      items_list--;}
    catch (out_of_range msg){}}


  void display(){           // funnction to display
    for (int i = 0; i < MAX_ITEMS - 1; i++){
      try{
        if (items[i] != nullptr){

          cout << *items[i] << "  ";}
        else{
          break;}}
      catch (...){
        cout << "The list is empty!";
        break;}}}

  bool IsEmpty(){               //function to see if the list is empty
    for (int i = 0; i < MAX_ITEMS; i++){
      if (items[i] != NULL){
        return false;}}
    return true;}
  
  bool IsFull(){            //function to see the list if full
    for (int i = MAX_ITEMS; i > 0; i--){
      opp++;
      if (items[i] == NULL)
      {
        return false;
      }}
    return true;}
 

  void MakeEmpty(){          //function to empty the list
    for (int i = 0; i < MAX_ITEMS; i++){
      if (items[i] != NULL){
        delete items[i];
        items[i] = NULL;}
      else{
        continue;}}}};



template <class T>              //OrderedList2 (inherited from OrderedList1)
class OrderedList2 : public OrderedList<T>
{
public:
  using OrderedList<T>::items;
  using OrderedList<T>::items_list;
  using OrderedList<T>::IsFull;

  void AddItem(T elem)
  {
    if (IsFull())
    {
      cout << "The Array of task 2 is full! and the maximum items are = " + to_string(MAX_ITEMS) + '\n';
      return;}
    for (int i = MAX_ITEMS - 1; i >= 0; i--){
      if (items[i] == nullptr){
        if (i == 0){
          items[i] = new T;
          *items[i] = elem;
          items_list++;
          break;}
        else if (items[i - 1] == nullptr){
          continue; }
        else if (elem < *items[items_list - 1]){
          continue;}
        else{
          items[i] = new T;
          *items[i] = elem;
          items_list++;
          opp++;
          break;}}
      else{
        if (elem < *items[i]){
          if (i != 0 && elem < *items[i - 1]){
            opp++;
            continue;}
          if (items_list == MAX_ITEMS){
            cout << "MSG: The Array of task 2 is full!  maximum items = " << to_string(MAX_ITEMS) << "\n";
            return;}
          for (int j = items_list - 1; j >= i; j--){
            items[j + 1] = items[j];}
          items[i] = new T;
          *items[i] = elem;
          items_list++;
          opp++;
          break;}}}}
  };


template <class T>      //OrderedList3 (inherited from OrderedList1)
class OrderedList3 : public OrderedList<T>
{
public:
  using OrderedList<T>::items;
  using OrderedList<T>::items_list;
  using OrderedList<T>::IsFull;

  int position = 0;
  int x = 0;
  int y = 0;                
  void addItem2(T element)
  { 
    int half = (0 + MAX_ITEMS) / 2; //definition for half which halfway of list
    for (int i = 0; i < MAX_ITEMS; i++)
    {
      opp++;
      if (IsFull()){
        break;}
      if (items[half] == NULL){
        items[half] = new T;
        *items[half] = element;
        opp++;
        break;
        }
      position++;
      if (position > half){
        x++;
        items[half + x] = new T;
        *items[half + x] = element;
        opp++;
        break;}

      else if (position < half){
        y++;
        items[half - y] = new T;
        *items[half - y] = element;
        opp++;
        break;
        }
    }
    int t = MAX_ITEMS;
    for (int i = 0; i < t - 1; i++){
      opp++;
      for (int j = 0; j < t - i - 1; j++){
        opp++;
        if (items[j] != NULL && items[j + 1] != NULL)
        {
          opp++;
          if (*items[j] > *items[j + 1])
          {
            opp++;
            swap(items[j], items[j + 1]);}}}}}

  void RemoveItem(T elem)
  {
    int position = -1;
    for (int i = 0; i < MAX_ITEMS; i++){
      if (items[i] == nullptr)
        continue;
      if (elem == *items[i]){
        opp++;
        position = i;
        break;}}
    if (position == -1)
    {
    }
    items[position] = nullptr;
    items_list--;
  }
  void display(){
    for (int i = 0; i < MAX_ITEMS; i++)
    {
      if (items[i] != nullptr){
        cout << *items[i] << ": ";
      }
    }
    }
};

int main()
{
  int task, t = 0;
  int n[MAX_ITEMS];

  cout << "Which task to you want to perform? (1 or 2 or 3) " ;
  cout   << endl;
  cin >> task;

  if (task == 1){
    for (t = 0; t < 100; t++){
      OrderedList<int> list_1;
      srand((unsigned)time(0));
      
      for (int i = 0; i < MAX_ITEMS; i++){
        n[i] = rand() % 101;
        list_1.AddItem(n[i]);}
      
      if (t == 0){
        cout << "The array for Task 1 is: ";
        cout<< endl;
        list_1.display();
        cout << endl;}

      for (int i = 0; i <= 24; i++){
        list_1.RemoveItem(n[i]);}
      
      if (t == 0){
        cout << endl;
        cout << "The Array for Task 1 after the deletion of random items is: ";
        cout << endl;
        list_1.display();}}}

  else if (task == 2){
    for (t = 0; t < 100; t++){
      OrderedList2<int> list_2;
      
      for (int i = 0; i < MAX_ITEMS; i++){
        n[i] = rand() % 101; 
        list_2.AddItem(n[i]);
        }

      if (t == 1){
        cout << endl;
        cout << "The array for Task 2 is: ";
        cout << endl;
        list_2.display();}

      for (int i = 0; i <= 24; i++){
        list_2.RemoveItem(n[i]);}

      if (t == 1){
        cout<< endl;
        cout << "The Array for Task 2 after the deletion of random items is: ";
        cout << endl;
        list_2.display();}}}
  
  else if (task == 3){
    for (t = 0; t < 100; t++){
      OrderedList3<int> list_3;
      
      for (int i = 0; i < MAX_ITEMS; i++){
        n[i] = rand() % 101;
        list_3.AddItem(n[i]);}

      if (t == 1){
        cout << endl;
        cout << "The array for Task 3 is: ";
        list_3.display();}

      for (int i = 0; i <= 24; i++){
        list_3.RemoveItem(n[i]);} 

      if (t == 1){
        cout << endl;
        cout << "The Array for Task 3 after the deletion of random items is: ";
        cout << endl;
        list_3.display();}}}

  cout << endl;
  cout << "The Number of increments are: ";
  cout << opp;
  return 1;
}