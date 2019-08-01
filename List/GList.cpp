typedef enum {ATOM, LIST} ElemTag; //ATOM==0: 原子, LIST==1: 子表
typedef AtomType int;

typedef struct GLNode{
    ElemTag tag; // 标示原子结点和表结点
    union{ // 原子结点和表结点的联合部分
        AtomType atom; // atom是原子结点的值域
        struct{
            struct ptr{ // 表结点的指针域
                GLNode * hp; // 指向表头
                GLNode * tp; // 指向表尾
            }
        };
    };
} * GList;
