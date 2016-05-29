#include <vector>
using std::vector;

template <typename elementType>
class HashTable
{
public:
    explicit HashTable (int size = 101)
    : array(nextPrime(size))
    {
        makeEmpty();
    }

    enum kindOfEntry {
        Active    ,
        Empty     ,
        Deleted  
    };  

    bool contains(const elementType & x) const
    {
        return isActive(findPos(x));
    }

    bool remove(const elementType & value)
    {
        int pos = findPos(value);
        if (!isActive(pos))
            return false;
    
        array[pos].info = Deleted;
        return true;
    }
    
    bool insert(const elementType & value) 
    {
        int pos = findPos(value);
        if (isActive(pos))
            return false;
        
        array[pos] = hashEntry(value, Active);
    
        if (++currentSize > array.size() / 2)
            rehash();
        return true;
    }

private:
    struct hashEntry 
    {
        elementType element;
        kindOfEntry info;

        hashEntry(const elementType & e = elementType(), kindOfEntry i = Empty)
        : element(e), info(i)
        { }
    };

    vector<hashEntry> array;
    int currentSize;

    void makeEmpty()
    {
        currentSize = 0;
        for (int i = 0; i < array.size(); i++)
            array[i].info = Empty;
    }

    bool isActive(int pos) const
    {
        return array[pos].info == Active;
    }

    int myhash(const elementType & x) const
    {
        return x % array.size();
    }

    // test whether an odd number is prime
    int isPrime(int num) 
    {
        for(int i = 3; i * i < num; i += 2) 
        {
            if(num % i == 0)
                return 0;
        }
        return 1;
    }

    int nextPrime(int num) 
    {
        if(num % 2 == 0)
            num++;
    
        for( ; ; num += 2) 
        {
            if(isPrime(num))
                break;
        }
        return num;
    }

    int findPos(const elementType & value) const
    {
        int offset = 1;
        int current = myhash(value);
    
        while(array[current].info != Empty && 
              array[current].element != value) {
            current += offset;
            offset += 2;
            if(current >= array.size())
                current -= array.size();
        }
    
        return current;
    }

    void rehash() 
    {
        vector<hashEntry> old = array;

        array.resize(nextPrime(2 * old.size()));
        for (int j = 0; j < array.size(); j++)
            array[j].info = Empty;

        currentSize = 0;
        for (int i = 0; i < old.size(); i++)
            if (old[i].info == Active)
                insert(old[i].element);
    }
};
