#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

/* 
 * INPUT: filename: which is argv[1]
 *      : thebintohide: binary to hide 
 * RETURN: totalbytes of the hidden program, needed to restore the file
 */
size_t hideme(char *filename)
{
    unlink(filename);
}


/* 
 * INPUT: filename: which is argv[2]
 *      : numbytes: binary to hide 
 * RETURN: totalbytes of the hidden program, needed to restore the file
 */
void restoreme(char *filename, char *bin, size_t numbytes)
{

    int out = open(filename, O_WRONLY | O_CREAT, 0644);

    write(out, bin, numbytes);

    close(out);

}
