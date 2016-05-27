/* test the valid syntax of #define macro */
/* NOT work: 
 * - 1name is not an identifier 
 * - name{}  it thinks {} is not part of the identifier
 * - (name)
 * - na(me   
 * - na)me   
 * - name[]   
 */
#define name[] "good"

int main(void) {
    printf("name is %s", name);

    return 0;
}
