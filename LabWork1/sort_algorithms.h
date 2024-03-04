#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <cstddef>
#include<cstdlib>
#include<ctime>
#include<QDebug>

template<class Tin>
class sort_algorithms
{
public:    
    sort_algorithms(const sort_algorithms& other) = delete;

    //Quick sort method Tested
    void static quickSort(Tin* array,int start, int end)
    {
        quickSortRec(array, start, end);
    }

private:
    sort_algorithms() = delete;
    //Operators
    sort_algorithms& operator = (const sort_algorithms& other) = delete;
    //Make the class abstract
    virtual void abs() = 0;
    //Recursive part of the function quickSort
    void static quickSortRec(Tin* array, int start, int end)
    {
        if(start < end)
        {
            int pivotIndex = 0;

            Randomize(array, start, end);

            pivotIndex = Partialize(array, start, end);

            quickSortRec(array, start, pivotIndex - 1);

            quickSortRec(array, pivotIndex + 1, end);
        }
    }
    //Randomly changes pivot point
    void static Randomize(Tin *array, int start, int end)
    {
        srand(std::time(nullptr));

        int randomIndex = 0;

        //Generate random index with a border check
        int range = end - start + 1;

        randomIndex = start + (rand() % range);

        qDebug() << "Index of the pivot: " << randomIndex;

        Tin pivot = *(array + randomIndex);//for debug

        Swap(array + randomIndex, array + end);//Swap pivot with last element of the array

        //Debug(array, end+1);
    }

    int static Partialize(Tin* array, int start, int end)
    {
        //Get pivot_point It is in the end of the array
        Tin* pivot = array + end;

        //Index of the last element that is lower then pivot point
        int lastLowerelement = start - 1;

        //Iterate array from start to end
        for(std::size_t j = start; j < end; ++j)
        {
            if( *(array + j) <= *pivot )//Element of the array is lower or equal the pivot
            {
                lastLowerelement++;

                Swap(array + j, array + lastLowerelement);

                //Debug(array, end+1);
            }
        }

        Swap(array + (lastLowerelement + 1), array + end);

        //Debug(array, end+1);

        return lastLowerelement + 1;
    }

    //Swap values of the 2 pointers
    void static Swap(Tin* l, Tin* r)
    {
        Tin temp = *l;

        *l = *r;

        *r = temp;
    }

    void static Debug(Tin* array, int size)
    {
        qDebug()<<"*******";

        for(int i = 0; i < size; ++i)
        {
            qDebug()<<*(array + i);
        }

        qDebug()<<"*******";
    }
};

#endif // SORT_ALGORITHMS_H
