#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
// Defining a structure for memory blocks
struct block
{
  struct block *prev;
  int block_no;
  int block_size;
  int process_no; // Process allocated to this block
  int free_space; // Free space left in the block
  struct block *next;
};
// Defining a structure for processes
struct process
{
  int status; // Block number where the process is allocated
  int process_no;
  int process_size;
};
int i, no_of_blocks, no_of_processes;
struct block *start = NULL, *end = NULL, *ptr = NULL, *new_block = NULL;
struct process processes[10];
// Function to display the details of blocks and processes
void display()
{
  printf(&quot;\nDetails of blocks:&quot;);
  printf(&quot;\nBlock no.\tBlock size\tFree space in block\tAllocated process no.&quot;);
  // Loop through each block and print its details
  for(ptr = start; ptr != NULL; ptr = ptr -&gt; next)
  {
    printf(&quot;\n%d\t\t&quot;, ptr -&gt; block_no);
    printf(&quot;%d\t\t&quot;, ptr -&gt; block_size);
    printf(&quot;%d\t\t\t&quot;, ptr -&gt; free_space);
    if(ptr -&gt; process_no == -1)
    printf(&quot;-&quot;);
    else
    printf(&quot;%d&quot;, ptr -&gt; process_no);
  }
  printf(&quot;\nDetails of processes:&quot;);
  printf(&quot;\nProcess no.\tProcess size\tAllocated to block no.&quot;);
  // Loop through each process and print its details
  for(i = 0; i &lt; no_of_processes; i++)
  {
    printf(&quot;\n%d\t\t&quot;, processes[i].process_no);
    printf(&quot;%d\t\t&quot;, processes[i].process_size);
    if(processes[i].status &gt;= 1)
    printf(&quot;%d&quot;, processes[i].status);
    else
    printf(&quot;Unallocated&quot;);
  }
}
// Function to perform first fit memory allocation
void first_fit()
{
  for(i = 0; i &lt; no_of_processes; i++)
  {
    for(ptr = start; ptr != NULL; ptr = ptr -&gt; next)
    {
      if(ptr -&gt; process_no == -1 &amp;&amp; ptr -&gt; block_size &gt;= processes[i].process_size)
      {
        processes[i].status = ptr -&gt; block_no;
        ptr -&gt; process_no = processes[i].process_no;
        ptr -&gt; free_space = ptr -&gt; free_space - processes[i].process_size;
        break;
      }
    }
  }
}
// Function to perform best fit memory allocation
void best_fit()
{
  int smallest_size;
  struct block *smallest;
  for(i = 0; i &lt; no_of_processes; i++)
  {
    smallest = NULL;
    smallest_size = 1000; // Dummy size to find the smallest block in the list
    // Find the smallest block that can accommodate the process
    for(ptr = start; ptr != NULL; ptr = ptr -&gt; next)
    {
      if(ptr -&gt; process_no == -1 &amp;&amp; ptr -&gt; block_size &gt;= processes[i].process_size &amp;&amp; ptr -&gt;
      block_size &lt;= smallest_size)
      {
        smallest = ptr;
        smallest_size = ptr -&gt; block_size;
      }
    }
    if(smallest != NULL)
    {
      // Allocate the process to the smallest block
      processes[i].status = smallest -&gt; block_no;
      smallest -&gt; process_no = processes[i].process_no;
      smallest -&gt; free_space = smallest -&gt; free_space - processes[i].process_size;
    }
  }
}
// Function to perform worst fit memory allocation
void worst_fit()
{
  int largest_size;
  struct block *largest;
  for(i = 0; i &lt; no_of_processes; i++)
  {
    largest = NULL;
    largest_size = 0; // Dummy size to find the largest block in the list
    // Find the largest block that can accommodate the process
    for(ptr = start; ptr != NULL; ptr = ptr -&gt; next)
    {
      if(ptr -&gt; process_no == -1 &amp;&amp; ptr -&gt; block_size &gt;= processes[i].process_size &amp;&amp; ptr -&gt;
      block_size &gt;= largest_size)
      {
        largest = ptr;
        largest_size = ptr -&gt; block_size;
      }
    }
    if(largest != NULL)
    {
      // Allocate the process to the largest block
      processes[i].status = largest -&gt; block_no;
      largest -&gt; process_no = processes[i].process_no;
      largest -&gt; free_space = largest -&gt; free_space - processes[i].process_size;
    }
  }
}
// Main function
void main()
{
  printf(&quot;Navaneeth K.B - S3 CSE-C&quot;);
  // Input number of blocks and their sizes
  printf(&quot;\nEnter no. of blocks: &quot;);
  scanf(&quot;%d&quot;, &amp;no_of_blocks);
  // Create blocks and initialize their details
  for(i = 0; i &lt; no_of_blocks; i++)
  {
    struct block *new_block = (struct block *)malloc(sizeof(struct block));
    new_block -&gt; prev = NULL;
    new_block -&gt; next = NULL;
    new_block -&gt; block_no = i + 1;
    new_block -&gt; process_no = -1;
    printf(&quot;Enter size of block %d: &quot;, i + 1);
    scanf(&quot;%d&quot;, &amp;new_block -&gt; block_size);
    new_block -&gt; free_space = new_block -&gt; block_size;
    if(start == NULL &amp;&amp; end == NULL)
    {
      start = end = new_block;
    }
    else
    {
      end -&gt; next = new_block;
      new_block -&gt; prev = end;
      end = new_block;
    }
  }
  // Input number of processes and their sizes
  printf(&quot;Enter no. of processes: &quot;);
  scanf(&quot;%d&quot;, &amp;no_of_processes);
  for(i = 0; i &lt; no_of_processes; i++)
  {
    processes[i].process_no = i + 1;
    printf(&quot;Enter size of process %d: &quot;, i + 1);
    scanf(&quot;%d&quot;, &amp;processes[i].process_size);
  }
  // First fit allocation
  printf(&quot;\nFirst fit allocation:&quot;);
  first_fit();
  display();
  // Clear allocations
  for(ptr = start; ptr != NULL; ptr = ptr -&gt; next)
  {
    ptr -&gt; process_no = -1;
    ptr -&gt; free_space = ptr -&gt; block_size;
  }
  for(i = 0; i &lt; no_of_processes; i++)
  {
    processes[i].status = -1;
  }
  
  // Best fit allocation
  printf(&quot;\n\nBest fit allocation:&quot;);
  best_fit();
  display();
  // Clear allocations
  for(ptr = start; ptr != NULL; ptr = ptr -&gt; next)
  {
    ptr -&gt; process_no = -1;
    ptr -&gt; free_space = ptr -&gt; block_size;
  }
  for(i = 0; i &lt; no_of_processes; i++)
  {
    processes[i].status = -1;
  }
  // Worst fit allocation
  printf(&quot;\n\nWorst fit allocation:&quot;);
  worst_fit();
  display();
}
