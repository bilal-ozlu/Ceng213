#include "Article.h"

/*#############################
#               NOTE!         #
#    Please don't forget to   #
#     check PDF. Fuctions     #
#    may have more detailed   #
#     tasks which are not     #
#       mentioned here.       #
#############################*/

Article::Article( int table_size,int h1_param, int h2_param )
{
    table = new std::pair<std::string, int>[table_size];
    for (int i = 0; i < table_size; i++) {
      table[i].first = EMPTY_KEY;
      table[i].second = EMPTY_INDEX;
    }
    n=0;
    this->h1_param = h1_param;
    this->h2_param = h2_param;
    this->table_size = table_size;
}

Article::~Article()
{
    delete[] table;
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const
{
    int count=0;
    int flag = 0;
    for (int j = 0; j < table_size; j++) {
        int hashv = (hash_function(key,j));
        if(1){
          if (flag){
            path.push_back(hash_function(key,j));
                  }
          else{
            flag=1;
              }
        }
        if (table[hashv].first == key){
          count++;
          if (count==nth){
            return table[hashv].second;
          }
        }
        else if(table[hashv].second == EMPTY_INDEX){
            return -1;
        }
      }
      return -1;
}

int Article::insert( std::string key, int original_index )
{
   if (getLoadFactor()>MAX_LOAD_FACTOR){
    expand_table();
    }
    int index = original_index;
    int probe=0;
    for (int j = 0; j < table_size; j++) {
        int hashv = (hash_function(key,j));
          if (table[hashv].first == EMPTY_KEY){
            table[hashv].first = key;
            table[hashv].second =index;
            n++;
            return probe;
          }
          else if(table[hashv].first==key && index<table[hashv].second){
            int temp = table[hashv].second;
            table[hashv].second = index;
            index = temp;
            }
          probe++;
    }
}

int Article::remove( std::string key, int nth )
{
  int count=0;
  int probe=-1;
  for (int j = 0; j < table_size; j++) {
      int hashv = (hash_function(key,j));
      if (table[hashv].first != key){
        probe++;
      }
      else if (table[hashv].first == key){
        count++;
        probe++;
        if (count==nth){
          table[hashv].first = EMPTY_KEY;
          table[hashv].second = MARKED_INDEX;
          n--;
          return probe;
        }
      }
    }
    return -1;
}

double Article::getLoadFactor() const
{
    return (double)n/(double)table_size;
}

void Article::getAllWordsFromFile( std::string filepath )
{
    std::ifstream f;
    f.open(filepath.c_str());
    while(f.good()){
      std::string w;
      int i=1;
      while(f>>w){
        insert(w,i++);
      }
    }
    f.close();
}

void Article::expand_table()
{
    int x = table_size*2;
    int y = table_size;
    table_size = nextPrimeAfter(x);
    h2_param = firstPrimeBefore(x);

    ntable = new std::pair<std::string, int>[table_size];
    for (int i = 0; i < table_size; i++) {
      ntable[i].first = EMPTY_KEY;
      ntable[i].second = EMPTY_INDEX;
    }
    n=0;
    for(int k = 0; k<y; k++){
      if (table[k].first!=EMPTY_KEY){
        ninsert(table[k].first,table[k].second);
      }
    }
    delete[] table;
    table = new std::pair<std::string, int>[table_size];
    for(int k = 0; k<table_size; k++){
        table[k].first = ntable[k].first;
        table[k].second = ntable[k].second;
      }
    delete[] ntable;
}

int Article::ninsert( std::string key, int original_index )
{
    int index = original_index;
    int probe=0;
    for (int j = 0; j < table_size; j++) {
        int hashv = (hash_function(key,j));
          if (ntable[hashv].first == EMPTY_KEY){
            ntable[hashv].first = key;
            ntable[hashv].second = index;
            n++;
            return probe;
          }
          else if(ntable[hashv].first==key && index<ntable[hashv].second){
            int temp = ntable[hashv].second;
            ntable[hashv].second = index;
            index = temp;
          }
          probe++;
    }
}

int Article::hash_function( std::string& key, int i ) const
{
    int x = convertStrToInt(key);
    return (h1(x) + h2(x)*i)%table_size;
}

int Article::h1( int key ) const
{
  int x = key;
  int pc = 0;
  while (x>0){
    pc+=x%2;
    x/=2;
  }
  return pc*h1_param;
}

int Article::h2( int key ) const
{
  int x = key % h2_param;
  return h2_param - x;
}
