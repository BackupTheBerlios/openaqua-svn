typedef void* BASE_TYPE;
typedef void* BASE_ARG_TYPE;

struct DLLNode
{
  DLLNode* pNext;
  DLLNode* pPrev;
  void* data;
};