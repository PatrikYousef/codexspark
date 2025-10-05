#ifndef CACHE_H
#define CACHE_H

// Läsning och sparning av JSON-cache
void lasJSONStack(const char *stad);
void lasJSONHeap(const char *stad);
void saveJSON(const char *stad, const char *data);

// Stack / Heap-menyer
void Stack();  // 📂 Visa JSON från stack
void Heap();   // 💾 Visa JSON från heap

#endif
