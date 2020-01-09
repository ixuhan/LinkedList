#include <stdio.h>
#include <stdlib.h>

//单链表的声明
typedef struct node_s{
    int value;
    struct node_s *next;
}node_s;

//标准返回值
typedef enum {
    OPERATE_OK = 0,
    OPERATE_ERR,
    OPERATE_MALLOC_ERROR,
    OPERATE_NOT_FOUND,
}operate_type_e;

//创建链表
operate_type_e CreateLinkedList(node_s **header)
{
    node_s *node = (node_s *)malloc(sizeof(node_s));
    if(node == NULL) {
        return OPERATE_MALLOC_ERROR;
    }
    node->value = 0;
    node->next = NULL;
    (*header) = node;
    return OPERATE_OK;
}

//添加节点
operate_type_e AddLinkedListNode(node_s *header,node_s *new_node)
{
    if(header == NULL || new_node == NULL) {
        return OPERATE_ERR;
    }
    
    node_s *header_temp = header;
    while(header_temp->next != NULL) {
        header_temp = header_temp->next;
    }
    header_temp->next = new_node;
    new_node->next = NULL;
    
    return OPERATE_OK;
}

//删除指定节点
operate_type_e DelLinkedListNode(node_s **header,node_s *del_node)
{
    if((*header) == NULL || del_node == NULL) {
        return OPERATE_ERR;
    }
    
    int isFindout = 0;
    node_s *temp_node = NULL;

    if(del_node == (*header)) {
        temp_node = (*header);
        (*header) = (*header)->next;
        free(temp_node);
        return OPERATE_OK;
    }

    node_s *header_temp = (*header);
    while(header_temp->next != NULL){
        if(header_temp->next == del_node) {
            temp_node = header_temp->next; 
            header_temp->next = header_temp->next->next;
            free(temp_node); 
            isFindout = 1;
            break;
        }
        header_temp = header_temp->next;
    }
    
    if(isFindout)
        return OPERATE_OK;
    else
        return OPERATE_NOT_FOUND;
}

//修改指定节点的值
operate_type_e ModifyLinkedListNodeValue(node_s *node,int new_value)
{
    if(node == NULL) {
        return OPERATE_ERR;
    }
    
    node->value = new_value;
    return OPERATE_OK;
}

//查找指定值的节点
operate_type_e FindLinkedListNode(node_s *header,int value,node_s **findout_node)
{
    if(header == NULL) {
        return OPERATE_ERR;
    }
    
    node_s *header_temp = header;
    while(header_temp != NULL) {
        if(header_temp->value == value) {
            (*findout_node) = header_temp;
            return OPERATE_OK;
        }
        header_temp = header_temp->next;
    }
    
    return OPERATE_NOT_FOUND;
}

//打印整个链表
void PrintLinkedList(node_s *header)
{
    if(header == NULL) {
        return;
    }
    
    node_s *header_temp = header;
    printf("\r\nnow linkedlist : ");
    while(header_temp != NULL) {
        printf("%d->",header_temp->value);
        header_temp = header_temp->next; 
    } 
    printf("\r\n"); 
} 

int main()
{
    node_s *my_linked_list = NULL;
    operate_type_e operate = CreateLinkedList(&my_linked_list);
    if(operate != OPERATE_OK) {
        printf("create my_linked_list error:%d\r\n",operate);
        return 0;
    }
    
    for(int i = 1;i < 5;i++) {
        node_s *new_node = (node_s *)malloc(sizeof(node_s));
        if(new_node == NULL) {
            printf("create new_node error!\r\n");
            break;
        }
        new_node->value = i;
        operate = AddLinkedListNode(my_linked_list,new_node);
        if(operate != OPERATE_OK) {
            printf("add linked_node error:%d\r\n",operate);
            break;
        }
    }
    PrintLinkedList(my_linked_list);
    
    node_s *findout_linked_node = NULL;
    operate = FindLinkedListNode(my_linked_list,1,&findout_linked_node);
    if(operate != OPERATE_OK) {
        printf("find linked_node error:%d\r\n",operate);
        return 0;
    }
    
    operate = ModifyLinkedListNodeValue(findout_linked_node,8);
    if(operate != OPERATE_OK) {
        printf("modify linked_node error:%d\r\n",operate);
        return 0;
    }
    PrintLinkedList(my_linked_list);
    
    operate = DelLinkedListNode(&my_linked_list,findout_linked_node);
    if(operate != OPERATE_OK) {
        printf("del linked_node error:%d\r\n",operate);
        return 0;
    }
    PrintLinkedList(my_linked_list);

    free(my_linked_list);
    return 0; 
} 