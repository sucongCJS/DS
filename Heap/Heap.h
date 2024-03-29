#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template<typename Item>
class MaxHeap{
private: // 不能直接修改
    Item* data;
    int count;
    int capacity;

    void shiftUp(int k){
        while(data[k] > data[k/2] && k > 1){ // k的取值最小到2
            swap(data[k], data[k/2]); //??优化swap
            k /= 2;
        }
    }

    void shiftDown(int k){
        while(k*2 <= count){
            int j = k*2; // data[j] 在最后是要和 data[k] 交换的
            if(j+1 <= count && data[j+1] > data[j])
                j++;
            if(data[k] >= data[j])
                break;
            swap(data[k], data[j]);
            k = j;
        }
    }

public:
    MaxHeap(int capacity){
        data = new Item[capacity + 1]; // 索引为0不存
        count = 0; // this 可以省略
        this->capacity = capacity;
    }

    // Heapify
    MaxHeap(Item arr[], int n){
        data = new Item[n + 1];
        capacity = n;

        for(int i=0; i<n; i++)
            data[i+1] = arr[i];
        count = n; // 虽然说这行放前面也行, 但语义上到这一步data才有值, count才不能为0

        for(int i=count/2; i>=1; i--)
            shiftDown(i);
    }

    ~MaxHeap(){
        delete[] data;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    void insert(Item item){
        assert(count + 1 <= capacity); //??分配新的空间

        data[++count] = item;
        shiftUp(count);
    }
    Item extracMax(){
        assert(count > 0);

        Item ret = data[1];
        swap(data[count--], data[1]);
        shiftDown(1);

        return ret;
    }

public:
    // 以树状打印整个堆结构
    void testPrint(){

        // 我们的testPrint只能打印100个元素以内的堆的树状信息
        if( size() >= 100 ){
            cout<<"This print function can only work for less than 100 int";
            return;
        }

        // 我们的testPrint只能处理整数信息
        if( typeid(Item) != typeid(int) ){
            cout <<"This print function can only work for int item";
            return;
        }

        cout<<"The max heap size is: "<<size()<<endl;
        cout<<"Data in the max heap: ";
        for( int i = 1 ; i <= size() ; i ++ ){
            // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
            assert( data[i] >= 0 && data[i] < 100 );
            cout<<data[i]<<" ";
        }
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }
private:
    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
};

template<typename Item>
class IndexMaxHeap{
    private: // 不能之间修改
    Item* data;
    int* indexes; // 堆
    int* reverse; // 索引
    // 通过堆可以很容易找到data, 通过data的顺序的那个索引值却不好找在堆中的位置, 所以要reverse来存储顺序的那个索引在堆中的位置, 以反向查找
    int count;
    int capacity;

    void shiftUp(int k){
        // 比较的是data, 变化的是index
        while(data[indexes[k]] > data[indexes[k/2]] && k > 1){ // 先获取存储的索引, 
            swap(indexes[k], indexes[k/2]);
            reverse[indexes[k]] = k; // indexes[k]的是顺序的索引, 要能通过顺序的索引找到它在堆中的位置
            reverse[indexes[k/2]] = k/2;
            k /= 2;
        }
    }

    void shiftDown(int k){
        while(k*2 <= count){
            int j = k*2; // data[j] 在最后是要和 data[k] 交换的
            if(j+1 <= count && data[indexes[j+1]] > data[indexes[j]])
                j++;
            if(data[indexes[k]] >= data[indexes[j]])
                break;
            swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;

            k = j;
        }
    }

public:
    IndexMaxHeap(int capacity){
        data = new Item[capacity + 1];
        indexes = new int[capacity + 1]; // 索引为0不存
        reverse = new int[capacity + 1];
        for(int i=0; i<=capacity; i++){
            reverse[i] = 0; // 索引如果不存在设为0
        }
        count = 0; // this 可以省略
        this->capacity = capacity;
    }

    ~IndexMaxHeap(){
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    // i从0开始 O(logn)
    void insert(int i, Item item){
        assert(count + 1 <= capacity); //??分配新的空间
        assert(i+1 >= 1 && i + 1 <= capacity);

        i++;
        data[i] = item; // 不能在相同索引的位置前后insert两次item的
        indexes[count+1] = i; // 索引列加上一位, 为新插入的
        reverse[i] = count+1;

        count++;
        shiftUp(count);
    }

    // O(logn)
    Item extracMax(){
        assert(count > 0);

        Item ret = data[indexes[1]];
        swap(indexes[count], indexes[1]);
        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0; // 将最后一个删除

        count--;
        shiftDown(1);

        return ret;
    }

    int extracMaxIndex(){
        assert(count > 0);

        int ret = indexes[1]-1;
        swap(indexes[count], indexes[1]);
        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0; // 将最后一个删除

        count--;
        shiftDown(1);

        return ret;
    }

    bool contain(int i){
        assert(i+1 >= 1 && i+1 <= capacity);
        return reverse[i+1] != 0;
    }

    Item getItem(int i){
        assert(contain(i));
        return data[i+1];
    }

    // O(n+logn) = O(n)
    void change(int i, Item newItem){
        assert(contain(i));
        i++;
        data[i] = newItem;

        // 找到indexes[j] = i, j表示data[i]在堆中的位置
        // 然后做一次shiftDown(j), 一次shiftUp(j)
        // for(int j=1; j<count; j++){
        //     if(indexes[j] == i){
        //         shiftDown(j);
        //         shiftUp(j);
        //         return;
        //     }
        // }
        int j = reverse[i];
        shiftDown(j);
        shiftUp(j);
        return;
    }
};

#endif