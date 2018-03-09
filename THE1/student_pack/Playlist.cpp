#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */
void Playlist::load(std::string fileName){
  ifstream file;
	string line;

	file.open(fileName.c_str());

	while(file.good( ))
	{
		getline(file, line);
    string title = line.substr(0,line.find(";"));
    line = line.substr(line.find(";")+1);
    string genre = line.substr(0,line.find(";"));
    line = line.substr(line.find(";")+1);
    string year = line.substr(line.find(";")+1);

    Entry entry(title, genre, year);
    insertEntry(entry);
		if( file.peek() == EOF ){
	     file.close();
     }
  }
}

void Playlist::insertEntry(const Entry &e){
  entries.insertNode(entries.getTail(), e);
  HistoryRecord hist(INSERT,e);
  history.push(hist);

}

void Playlist::deleteEntry(const std::string &_title){
  if (entries.isEmpty()){
    return;
  }

  Node<Entry>* p = entries.getHead();
  if(p->getData().getTitle() == _title){
    entries.setHead(p->getNext());
    HistoryRecord hist(DELETE,p->getData());
    history.push(hist);
    return;
  }
  p=p->getNext();
  while (p){
    if(p->getData().getTitle() == _title){
        Node<Entry>* prev = entries.findPrev(p->getData());
        entries.deleteNode(prev);
        HistoryRecord hist(DELETE,p->getData());
        history.push(hist);
        break;
  }
    p = p->getNext();
}
}

void Playlist::moveLeft(const std::string &title){
  if (entries.isEmpty()){
    return;
  }
  Node<Entry>* p = entries.getHead();
  if (p->getData().getTitle() == title){
    return;
  }
  if (p->getNext()->getData().getTitle() == title){

    Entry e(p->getData().getTitle(), p->getData().getGenre(), p->getData().getYear());
    entries.setHead(p->getNext());
    entries.insertNode(entries.getHead(), e);
    return;
  }

  while(p->getNext()->getNext()){
    if(p->getNext()->getNext()->getData().getTitle() == title){
      Entry e(p->getNext()->getNext()->getData().getTitle(), p->getNext()->getNext()->getData().getGenre(), p->getNext()->getNext()->getData().getYear());
      entries.deleteNode(p->getNext());
      entries.insertNode(p, e);
      break;
    }
    p = p->getNext();
  }
}

void Playlist::moveRight(const std::string &title){
  if (entries.isEmpty()){
    return;
  }
  if (entries.getTail()->getData().getTitle() == title){
    return;
  }
  Node<Entry>* p = entries.getHead();
  if (p->getData().getTitle() == title){
    Entry e(p->getData().getTitle(), p->getData().getGenre(), p->getData().getYear());
    entries.setHead(p->getNext());
    entries.insertNode(entries.getHead(), e);
    return;
  }

  while(p->getNext()){
    if(p->getData().getTitle() == title){
      moveLeft(p->getNext()->getData().getTitle());
      break;
    }
    p = p->getNext();
  }
}

void Playlist::reverse(){
    MyStack<Entry> rev;
    Node<Entry>* p = entries.getHead();
    while(p){
      rev.push(p->getData());
      p=p->getNext();
    }
    entries.clear();
    while(!rev.isEmpty()){
      entries.insertNode(entries.getTail(), rev.Top()->getData());
      rev.pop();
    }
    HistoryRecord hist(REVERSE);
    history.push(hist);
}

void Playlist::sort(){
    for(int i=0 ; i<entries.getSize()-1 ; i++){
          Node<Entry>* p = entries.getHead();
          int k=i;
          int l=0;
          while(k>0){
            p=p->getNext();
            k--;
          }
          string mini = p->getData().getTitle();
          for(int j=i+1;j<entries.getSize()-1;j++){
              Node<Entry>* q = entries.getHead();
              k=j;
              while(k>0){
                q=q->getNext();
                k--;
              }
              string x = q->getData().getTitle();
              if (x.compare(mini)<0){
                mini = x;
                l=j;
              }
            }
              if (mini!=p->getData().getTitle()){
                k=l-i;
                while(k>0){
                  moveRight(p->getData().getTitle());
                  k--;
                }
                k=l-i-1;
                while(k>0){
                  moveLeft(mini);
                  k--;
          }
      }
  }
  Node<Entry>* w1 = entries.getTail();
  Node<Entry>* w3;
  int ais=entries.getSize();
  while(ais>0){
    w3=entries.findPrev(w1->getData());
    string w4 = w3->getData().getTitle();
    string w2 = w1->getData().getTitle();
    if (w2.compare(w4)<0){
      moveLeft(w1->getData().getTitle());
    }
    if(w2.compare(w4)>0){
      break;
    }
    ais--;
}
}

void Playlist::merge(const Playlist & pl){
Node<Entry>* second =pl.entries.getHead();
Node<Entry>* p =entries.getHead();
  while(second){
  while(p){
      string p1 = p->getData().getTitle();
      string s1 = second->getData().getTitle();

      if (p1.compare(s1)>0){
        entries.insertNode(entries.findPrev(p->getData()),second->getData());
        break;
      }
      if (p==entries.getTail()){
          entries.insertNode(entries.getTail(),second->getData());
          break;
      }
      p=p->getNext();
  }
        second=second->getNext();
  }
}


void Playlist::shuffle(){
  Entry en("b1", "b2", "b3");
  insertEntry(en);
  for (int i = 0; i < entries.getSize()-2; i++) {
    int j = getRandomNumber(i,entries.getSize()-1);
    Node<Entry>* p = entries.getHead();
    Node<Entry>* q = entries.getHead();
    int k=i;
    while(k>0){
      p=p->getNext();
      k--;
    }
    k=j;
    while(k>0){
      q=q->getNext();
      k--;
    }
    k=j-i;
    while(k>0){
      moveRight(p->getData().getTitle());
      k--;
    }
    k=j-i-1;
    while(k>0){
      moveLeft(q->getData().getTitle());
      k--;
    }
  }
  deleteEntry("b1");
  history.pop();
  history.pop();
}

void Playlist::undo(){
  if (!history.isEmpty()){
    if (history.Top()->getData().getOperation()==INSERT){
      deleteEntry(history.Top()->getData().getEntry().getTitle());
      history.pop();
      history.pop();
  }
    else if (history.Top()->getData().getOperation()==DELETE){
      insertEntry(history.Top()->getData().getEntry());
      history.pop();
      history.pop();
  }
    else if (history.Top()->getData().getOperation()==REVERSE){
      reverse();
      history.pop();
      history.pop();
    }
}
}
