typedef int LType;

typedef struct node_s {
	LType data;
	struct node_s* next;
}node_t;

node_t* getnode(void)
{
	node_t* node;
	node = (node_t*)malloc(sizeof(node_t));
	node->next = NULL;
	return (node);
}

node_t* addBeginning(node_t* hp, LType item) {
	node_t* newp;
	newp = getnode();
	newp->next = hp;
	newp->data = item;
	return (newp);
}

void addAfter(node_t* p, LType item) {
	node_t* newp;
	newp = getnode();
	newp->next = p->next;
	p->next = newp;
	newp->data = item;
}

void deleteAfter(node_t* p, LType* item) {
	node_t* del;
	del = p->next;
	p->next = del->next;
	*item = del->data;
	free(del);
}

node_t* deleteFirst(node_t* hp, LType* item) {
	node_t* del;
	del = hp;
	hp = del->next;
	*item = del->data;
	free(del);
	return(hp);
}