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