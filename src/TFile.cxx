#include <TFile.h>

void tfile_append(tfile_t* head, string data) {
	tfile_t c = nullptr; // current node

	tfile_t n = (tfile_t) malloc(sizeof(tfile_t));
	n->data = data;
	n->next = nullptr;

	if (*head == nullptr) {
		*head = n;
	} else {
		c = *head;
		
		while (c->next != nullptr) {
			c = c->next;
		}

		c->next = n;
	}
}

void tfile_print(tfile_t* head) {
	tfile_t c = *head;

	if (c == nullptr) {
		printf("file not found\n");
	}
	
	while (c != nullptr) {
		printf("List: %s\n", c->data);
		c = c->next;
	}
}

void tfile_clear(tfile_t* head) { 
	tfile_t c = *head;
	tfile_t next;

	while (c != NULL) {
		next = c->next;
		free(c);
		c = next;
	}

	*head = NULL;
}

extern tfile_t result;
void tfile_search(tfile_t* _head, cstring key) {
	tfile_t c = *_head;

	while (c != NULL) {
		if (strstr(c->data, key) != NULL) {
			printf("result: %s\n", c->data);
			tfile_append(&result, c->data);
		} 
			
		c = c->next;
	}
}