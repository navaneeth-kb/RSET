#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int NFA[MAX][MAX][MAX];
int DFA[MAX][MAX];
int DFA_states[MAX][MAX];
int nfa_count;
int nfa_symbols;
int dfa_count=0;
int visited[MAX];
char symbols[MAX];

int findState(int state[])
{
    for (int i=0;i<dfa_count;i++)
    {
        int same=1;
        for (int j=0;j<nfa_count;j++)
        {
            if (DFA_states[i][j] != state[j])
            {
                same = 0;
                break;
            }
        }
        if (same==1)
        {
            return i;
        }
    }
    return -1;
}

int addState(int state[])
{
    for (int i=0;i<nfa_count;i++)
    {
        DFA_states[dfa_count][i]=state[i];
    }
    return dfa_count++;
}

int main()
{
    printf("Enter the number of NFA states:");
    scanf("%d",&nfa_count);

    printf("Enter the number of input symbols:");
    scanf("%d",&nfa_symbols);
    printf("Enter symbols:");
    for(int i=0;i<nfa_symbols;i++)
    {
        char s;
        scanf(" %c",&s);
        symbols[i]=s;
    }

    for (int i=0;i<nfa_count;i++)
    {
        for (int sym=0;sym<nfa_symbols;sym++)
        {
            int count=0;
            printf("Enter number of transitions from state %d to symbol %d: ",i,sym);
            scanf("%d",&count);

            printf("Enter destination states:");
            for (int j=0;j<count;j++)
            {
                int next;
                scanf("%d",&next);
                NFA[i][sym][next]=1;
            }
        }
    }

    int start[MAX]={0};
    start[0]=1;
    addState(start);

    memset(visited,0,sizeof(visited));

    for (int i=0;i<dfa_count;i++)
    {
        if (visited[i])
        {
            continue;
        }
        visited[i] = 1;

        for(int sym=0;sym<nfa_symbols;sym++)
        {
            int new_state[MAX]={0};
            for (int s=0;s<nfa_count;s++)
            {
                if (DFA_states[i][s])
                {
                    for (int next=0;next<nfa_count;next++)
                    {
                        if (NFA[s][sym][next])
                        {
                            new_state[next]=1;
                        }
                    }
                }
            }
            int idx=findState(new_state);
            if (idx==-1)
            {
                idx=addState(new_state);
            }

            DFA[i][sym] = idx;
        }
    }

    //Display
    
    printf("\nDFA Transition Table\n")
    printf("States\t");
    for (int i=0;i<nfa_symbols;i++)
    {
        printf("%c\t",symbols[i]);
    }
    printf("\n");

    for (int i=0;i<dfa_count;i++)
    {
        printf("{");
        for (int s=0;s<nfa_count;s++)
        {
            if (DFA_states[i][s])
            {
                printf("%d",s);
            }
        }
        printf("}\t\t");

        for (int sym=0;sym<nfa_symbols;sym++)
        {
            printf("{");
            for (int s=0;s<nfa_count;s++)
            {
                if (DFA_states[DFA[i][sym]][s])
                {
                    printf("%d",s);
                }
            }
            printf("}\t\t");
        }
        printf("\n");
    }

    return 0;
}

