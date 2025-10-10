#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_ALPHABET 20

int nfa[MAX_STATES][MAX_ALPHABET][MAX_STATES]; // nfa[state][symbol][state] = 1 if transition exists
int dfa[MAX_STATES][MAX_ALPHABET];
int nfa_states, symbols;
char symbol[MAX_ALPHABET];
int dfa_states_count = 0;

// To store DFA states as sets of NFA states
int dfa_states[MAX_STATES][MAX_STATES];
int marked[MAX_STATES];

// Check if DFA state already exists
int state_exists(int state[], int count) {
    for (int i = 0; i < dfa_states_count; i++) {
        int match = 1;
        for (int j = 0; j < nfa_states; j++) {
            if (dfa_states[i][j] != state[j]) {
                match = 0;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

// Add new DFA state
int add_state(int state[]) {
    for (int i = 0; i < nfa_states; i++) {
        dfa_states[dfa_states_count][i] = state[i];
    }
    return dfa_states_count++;
}

int main() {
    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("Enter symbols (no spaces): ");
    for (int i = 0; i < symbols; i++) {
        scanf(" %c", &symbol[i]);
    }

    // Initialize NFA transitions
    memset(nfa, 0, sizeof(nfa));
    for (int i = 0; i < nfa_states; i++) {
        for (int j = 0; j < symbols; j++) {
            int k, num;
            printf("Enter number of transitions from state %d on symbol %c: ", i, symbol[j]);
            scanf("%d", &num);
            printf("Enter destination states: ");
            for (k = 0; k < num; k++) {
                int dest;
                scanf("%d", &dest);
                nfa[i][j][dest] = 1;
            }
        }
    }

    // Initialize DFA start state
    int start[MAX_STATES] = {0};
    start[0] = 1; // assuming state 0 is the start
    add_state(start);

    // Subset construction
    memset(marked, 0, sizeof(marked));
    for (int i = 0; i < dfa_states_count; i++) {
        marked[i] = 1;
        for (int j = 0; j < symbols; j++) {
            int new_state[MAX_STATES] = {0};
            for (int k = 0; k < nfa_states; k++) {
                if (dfa_states[i][k]) {
                    for (int l = 0; l < nfa_states; l++) {
                        if (nfa[k][j][l]) new_state[l] = 1;
                    }
                }
            }
            int index = state_exists(new_state, nfa_states);
            if (index == -1) {
                index = add_state(new_state);
            }
            dfa[i][j] = index;
        }
    }

    // Print DFA
    printf("\nDFA Transition Table:\n");
    printf("State\t");
    for (int i = 0; i < symbols; i++) {
        printf("%c\t", symbol[i]);
    }
    printf("\n");

    for (int i = 0; i < dfa_states_count; i++) {
        printf("{");
        for (int k = 0; k < nfa_states; k++) {
            if (dfa_states[i][k]) printf("%d", k);
        }
        printf("}\t");
        for (int j = 0; j < symbols; j++) {
            printf("{");
            for (int k = 0; k < nfa_states; k++) {
                if (dfa_states[dfa[i][j]][k]) printf("%d", k);
            }
            printf("}\t");
        }
        printf("\n");
    }

    return 0;
}
