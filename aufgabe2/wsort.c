#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_WORD 100

// Function to compare two strings
static int compare(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

// Function to free all allocated words
static void freeWords(char **words, size_t num_words)
{
  for (size_t i = 0; i < num_words; i++)
  {
    free(words[i]);
  }
  free(words);
}

// Input contains many lines
// Each line contains one word
// Each word contains array of characters
// Function reads input words into an array
static char **read_lines(size_t *num_lines)
{
  size_t size = 0;     // number of stored words
  size_t capacity = 0; // number of slots allocated in lines
  char **lines = NULL;
  char buffer[MAX_LENGTH_WORD + 1]; // +1 for null terminator; on stack, so nothing to free
  size_t len_word = 0; // Length of the current word
  int too_long = 0;    // Flag to indicate if the word is too long
  for (;;)
  {
    int ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF)
    {
      // Case 1: Line is too long
      if (too_long)
      {
        fprintf(stderr, "Line has more than 100 characters\n");
      }
      // Case 2: Normal valid line
      else if (len_word > 0)
      {
        buffer[len_word] = '\0';
        char *word = strdup(buffer);
        if (word == NULL)
        {
          perror("strdup");
          freeWords(lines, size);
          exit(EXIT_FAILURE);
        }
        // Array full: double capacity so realloc runs only O(log n) times
        if (size == capacity)
        {
          size_t new_capacity = (capacity == 0) ? 16 : capacity * 2;
          char **new = realloc(lines, new_capacity * sizeof(char *));
          if (new == NULL)
          {
            perror("realloc");
            free(word);
            freeWords(lines, size);
            exit(EXIT_FAILURE);
          }
          lines = new;
          capacity = new_capacity;
        }
        lines[size++] = word;
      }
      // Reset for the next line
      len_word = 0;
      too_long = 0;
      if (ch == EOF)
      {
        break;
      }
    }
    // Case 3: Normal character
    else
    {
      if (len_word < MAX_LENGTH_WORD)
      {
        buffer[len_word++] = (char)ch;
      }
      else
      {
        too_long = 1;
      }
    }
  }
  if (ferror(stdin))
  {
    perror("fgetc");
    freeWords(lines, size);
    exit(EXIT_FAILURE);
  }
  *num_lines = size;
  return lines;
}

static void printWords(char **words, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    if (fputs(words[i], stdout) == EOF)
    {
      perror("fputs");
      freeWords(words, size);
      exit(EXIT_FAILURE);
    }
    if (fputc('\n', stdout) == EOF)
    {
      perror("fputc");
      freeWords(words, size);
      exit(EXIT_FAILURE);
    }
  }
  if (fflush(stdout) == EOF)
  {
    perror("fflush");
    freeWords(words, size);
    exit(EXIT_FAILURE);
  }
}

int main(void)
{
  size_t num_lines = 0;
  char **lines = read_lines(&num_lines);
  qsort(lines, num_lines, sizeof(char *), compare);
  printWords(lines, num_lines);
  freeWords(lines, num_lines);
  return EXIT_SUCCESS;
}