#ifndef HIGHLIGHTOBJECT_H
#define HIGHLIGHTOBJECT_H

#include <stdlib.h>
#include <qvaluelist.h>
class HighlightObject;
typedef QValueList<HighlightObject *>HighlightList;


//! A simple object to describe which lines to highlight and in what color.
/*! \class HighlightObject
    This class is used by SourcePanel to highlight particular lines with 
    a specific color.
 */
class HighlightObject
{
public:
    HighlightObject()
    {
      // Default constructor.  Not used.
      line = 0;
      description = "none";
    };

    HighlightObject(QString fn, int l, char *c="red", char *d="N/A")
    {
      fileName = fn;
      line = l;
      color = strdup(c);
      description = strdup(d);
    };

    ~HighlightObject()
    {
//      dprintf("delete HighlightObject %s\n", description);
      if( description )
      {
        free(description);
      }
      if( color )
      {
        free(color);
      }
    }

    void print()
    {
      printf("%d %s %s\n", line, color, description);
    }

    QString fileName;
    int line;
    char *color;
    char *description;
};
#endif // HIGHLIGHTOBJECT_H
