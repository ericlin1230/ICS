#include <windows.h>
#include <iostream>
#include <math.h>
#include <time.h>  // needed for time function
#include <stdio.h>
#include <stdlib.h>
/* glut.h includes gl.h and glu.h */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Eric Lin
// 2017/06/15
// To play the game reversi, the game rules and instructions can be found in the user manual.  The goal is to beat the other player with more amount of own disks on the board

using namespace std;

int disks[8][8]; // set up the array for disks
// let black be 1, white be 2, nothing be 0
int undodisks[8][8]; // array for undo
int turn; // record the current turn
bool ok=true; // to check if the move is invalid or not
int black=2;
int white=2; // to count how many of current each player
int clickx,clicky; // what the user clicked
int clickx1,clicky1;  // for undo
int initi; // first round setting int
bool win=false; // for display
int win1; // for esc
int black1,white1; // for undo
bool whitewin=false; // bool for win
bool blackwin=false; // bool for win
bool undo;

void keyPressed (unsigned char key, int x, int y)
{
    if (key == 27)              // Escape key
    {
        glutDestroyWindow (win);
        exit (0);
    }
    //glutPostRedisplay();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) // function used to draw a white circle
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
//GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.14159265358979;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0,1.0); // white color
    glVertex2f(x, y); // center of circle
    glColor3f(0.65, 0.65, 0.65); // a bit gray


    for(i = 0; i <= triangleAmount; i++) // draw the triangles to draw filled circle
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }

    glEnd();
}
void drawFilledCircleY(GLfloat x, GLfloat y, GLfloat radius) // function used to draw a white circle
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
//GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.14159265358979;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0,0.0); // white color
    glVertex2f(x, y); // center of circle


    for(i = 0; i <= triangleAmount; i++) // draw the triangles to draw filled circle
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }

    glEnd();
}
void drawFilledCircleB(GLfloat x, GLfloat y, GLfloat radius) // function used to draw a black circle
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
//GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.14159265358979;
    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0.5, 0.5, 0.5); // gray
    glVertex2f(x, y); // center of circle
    glColor3f(0.0, 0.0, 0.0); // black
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void printb() // show the current board on console
{
    for(int i=0; i<8; i++)
    {
        for (int f=0; f<8; f++)
        {
            cout<<disks[f][i]; // print the board
            cout<<" "; // space
        }
        cout<<endl; // skip line
    }
}


void renderBitmapString(float x, float y, void *font, const char *string)  // function to print text
{
    const char *c;
    glRasterPos3f(x, y, 0);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}


void checkm(int x, int y) // method to check and change the point the user clicks
{
    bool pass; // boolean to check pass
    int oppo; // the variable for the opponent number
    if(turn==1) // if current player is 1
        oppo=2; // the opponent is 2
    else if (turn==2) // if current is 2
        oppo=1; // oppoenent is 1
    pass=false; // pass is initially set as false

    if(disks[x][y]==1 || disks[x][y]==2) // if user clicks on a block that already contains disks
        pass=false; // pass is false


    if(disks[x][y]!=1 && disks[x][y]!=2)
    {
        // convert check
        if(x-1>=0) // check the ones on the left
        {
            int chang=0; // set the amount of change
            int ch1; // record the spot of change
            bool empt=false; // check if there is empty
            if(disks[x-1][y]==oppo) // if the disk on the left is opposite
            {
                int ch=x-1;
                while(true) // keep checking left
                {
                    if(disks[ch][y]==turn && chang==0) // if there is another same one after the first one being opposite
                    {
                        ch1=ch; // record the spot of change
                        chang=1; // set chang to 1 so it doesnt keep going
                        break;
                    }
                    if(ch==0) // if it reaches the boundary
                        break; // break
                    ch--; // go left more
                    if(disks[ch][y]==0) // if there is no more disk
                    {
                        empt=true; // let empty be true
                        break; // break
                    }
                }
                if(empt==false) // if it is not empty
                {
                    if(chang==1) // if there is valid move
                    {
                        for(int ch=x; ch>ch1; ch--) // for all the disks in between
                        {
                            disks[ch][y]=turn; // convert the ones in between
                            pass=true; // let pass be true so invalid is not displayed
                        }
                    }
                }
            }
        }
        if(y-1>=0) // check the ones on the above
        {
            int cou=0; // set count variable
            int chang=0; // set the amount of change
            int ch1; // record the spot of change
            bool empt=false; // check if there is empty
            if(disks[x][y-1]==oppo) // if the disk on the above is opposite
            {
                int ch=y-1;
                while(true) // keep checking above
                {
                    //   if(empt==false) //there is not any empty
                    //   {
                    if(disks[x][ch]==turn && chang==0) // if there is another same one after the first one being opposite
                    {
                        ch1=ch; // record the spot of change
                        chang=1; // set chang to 1 so it doesnt keep going
                        break;
                    }
                    //   else if (disks[ch][y]==0)
                    //      empt=true; // if it is empty, stop the process
                    //}

                    cou++; // count
                    if(ch==0) // if it reaches the boundary
                        break; // break;
                    ch--; // goes up more
                    if(disks[x][ch]==0) // if it is empty
                    {
                        empt=true; // empty is true
                        break; // break
                    }
                }
                if(empt==false) //   if it is not empty
                {
                    if(chang==1) // if there is a change
                    {
                        for(int ch=y; ch>ch1; ch--) // for every disks in between
                        {
                            disks[x][ch]=turn; // convert the ones in between
                            pass=true; // set pass to true
                        }
                    }
                }
            }
        }

        if(y+1<8) // check the ones on the bottom
        {
            int chang=0; // set the amount of change
            int ch1; // record the spot of change
            bool empt=false; // check if there is empty
            if(disks[x][y+1]==oppo) // if the disk on the bottom is opposite
            {
                int ch=y+1;
                while(true) // keep checking bottom
                {
                    if(disks[x][ch]==turn && chang==0) // if there is another same one after the first one being opposite
                    {
                        ch1=ch; // record the spot of change
                        chang=1; // set chang to 1 so it doesnt keep going
                        break;
                    }
                    if(ch==7) // if it reaches the boundary
                    {
                        if (disks[x][ch]==oppo) // if it is the opposite
                        {
                            empt=true; // it is not going to change
                            break; // break
                        }
                    }
                    if(ch==7) // if it touches the boundary
                        break; // break
                    ch++; // moves down
                    if(disks[x][ch]==0) // if it is empty
                    {
                        empt=true; // set empty to true
                        break; // break
                    }
                }
                if(empt==false) // if it is not empty
                {
                    if(chang==1) // and there is one valid move
                    {
                        for(int ch=y; ch<ch1; ch++) // all disks between
                        {
                            disks[x][ch]=turn; // convert the ones in between
                            pass=true; // set pass to true
                        }
                    }
                }
            }
        }
        if(x+1<8) // check the ones on the right
        {
            int chang=0; // set the amount of change
            int ch1; // record the spot of change
            bool empt=false; // check if there is empty
            if(disks[x+1][y]==oppo) // if the disk on the right is opposite
            {
                int ch=x+1;
                while(true) // keep checking right
                {
                    if(ch<8) // if it does not hit the boundary
                    {
                        if(disks[ch][y]==turn && chang==0) // if there is another same one after the first one being opposite
                        {
                            ch1=ch; // record the spot of change
                            chang=1; // set chang to 1 so it doesnt keep going
                            break;
                        }
                    }
                    if(ch==7) // if it hits the boundary
                        break; // break
                    ch++; // moves right
                    if(disks[ch][y]==0)  // if it is empty
                    {
                        empt=true; // empty becomes true
                        break; // break
                    }
                }

                if(empt==false) // it is not empty
                {
                    if(chang==1) // if there is a move
                    {
                        for(int ch=x; ch<ch1; ch++) // every disks in between
                        {
                            disks[ch][y]=turn; // convert the ones in between
                            pass=true; // pass is true
                        }
                    }
                }
            }
        }
        if(x-1>=0 && y-1>=0) // left up
        {
            int y2=y-1; // up
            int x2=x-1; //  left
            int cou=0; // count
            if(disks[x-1][y-1]==oppo) // if the disk is opposite
            {
                while(true) // keep moving
                {
                    if(y2-1<0 || x2-1<0) // if it his the boundary
                        break; // break;
                    y2--; // move up
                    x2--; // move left
                    if(disks[x2][y2]==oppo) // if it is opposite
                    {
                        cou++; // add 1 to count
                    }
                    if(disks[x2][y2]==turn) // if it is the same one as current player
                    {
                        for(int i=0; i<cou+1; i++) // for all the ones in between
                        {
                            x2++; // move back
                            y2++; // move back
                            disks[x2][y2]=turn; // convert to current player
                        }
                        disks[x][y]=turn; // convert the place clicked
                        pass=true; // pass is true
                        break; // break
                    }
                    if(disks[x2][y2]==0) // if it is empty
                        break; // break
                }
            }
        }
        if(x+1<8 && y+1<8) // check the bottom right
        {
            int y2=y+1; // move down
            int x2=x+1; // move right
            int cou=0; // count
            if(disks[x+1][y+1]==oppo) // if the bottom right one is opposite
            {
                while(true) // keep moving
                {
                    if(y2+1>=8 || x2+1>=8) // if it hits boundary
                        break; // break
                    y2++; // keet moving
                    x2++; // keep moving
                    if(disks[x2][y2]==oppo) // if it is opposite
                    {
                        cou++; // count ++
                    }
                    if(disks[x2][y2]==turn) // if it meets the same color
                    {
                        for(int i=0; i<cou+1; i++) // for all in between
                        {
                            x2--; // move back
                            y2--; // move back
                            disks[x2][y2]=turn; // change color
                            pass=true; // pass is true
                        }
                        disks[x][y]=turn; // change the clikced block

                        break; // break
                    }
                    if(disks[x2][y2]==0) // if it is empty
                        break; // break
                }
            }
        }
        if(x+1<8 && y-1>=0) // check right up
        {
            int y2=y-1; // move up
            int x2=x+1; // move right
            int cou=0; // count
            if(disks[x+1][y-1]==oppo) // if it is opposite
            {
                while(true) // keeps going
                {
                    if(y2-1<0 || x2+1>=8) // if it hits the boundary
                        break; // break
                    y2--; // keep moving
                    x2++; // keep moving
                    if(disks[x2][y2]==oppo) // if it is the opposite
                    {
                        cou++; // count +1
                    }
                    if(disks[x2][y2]==turn) //  if it is the same one
                    {
                        for(int i=0; i<cou+1; i++)// for all the ones in between
                        {
                            x2--; // moves back
                            y2++; // moves back
                            disks[x2][y2]=turn; // change the ones to current color
                            pass=true; // pass is true
                        }
                        disks[x][y]=turn; // change the one clicked as well
                        break; // break
                    }
                    if(disks[x2][y2]==0) // if it is empty
                        break; // break
                }
            }
        }
        if(y+1<8 && x-1>=0) // down left
        {
            int y2=y+1; // move down
            int x2=x-1; // move left
            int cou=0; // count
            if(disks[x-1][y+1]==oppo) // if it is oppostie
            {
                while(true) // keep going
                {
                    if(x2-1<0 || y2+1>=8) // if it hits boundary
                        break; // break
                    y2++; // keep moving
                    x2--; // keep moving
                    if(disks[x2][y2]==oppo) // if it is opposite
                    {
                        cou++; // count ++
                    }
                    if(disks[x2][y2]==turn) // if it is the same as current
                    {
                        for(int i=0; i<cou+1; i++) // for all in between
                        {
                            x2++; // move back
                            y2--; // move back
                            disks[x2][y2]=turn; // change the disks
                            pass=true; // pass is true
                        }
                        disks[x][y]=turn; // changed clicked
                        break; // break
                    }
                    if(disks[x2][y2]==0) // if it is empty
                        break; // break
                }
            }
        }
    }
    if(pass==true) // if pass
    {
        if(turn==1)
            turn=2; // switch turn
        else if(turn==2)
            turn=1; // switch turn
        ok=true; // ok is true
        clickx=x;
        clicky=y;
        initi++;
        cout<<initi<<"ffff"<<endl;
    }
    else ok=false; // if not pass ok is false
    black=0; // set black to 0
    white=0; // set white to zero
    for(int i=0; i<8; i++) // for all board
    {
        for(int f=0; f<8; f++) // for all board
        {
            if(disks[i][f]==1)
                black++; // count black
            if(disks[i][f]==2)
                white++; // count white
        }
    }

}

void OnMouseClick(int button, int state, int x, int y) // for mouse function
{
    if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) // if left buutton is clicked down
    {
        //store the x,y value where the click happened
        if(x>50 && x<850 && y>100 && y<900 && whitewin==false && blackwin==false) // if it is board range
        {
            for(int i=0; i<8; i++) // for all board
            {
                for(int f=0; f<8; f++) // for all board
                {
                    undodisks[i][f]=disks[i][f];
                }
            }
            undo=false;
            black1=black;
            white1=white;
            clickx1=clickx;
            clicky1=clicky;
            int x1=(x-50)/100; // convert to array number
            int y1=(y-100)/100; // convert to array number
            checkm(x1,y1); // check and change
            printb(); // print in console
        }
        cout<<x<<","<<y<<endl;
        if(x>900 && x<975 && y>200 && y<250) // if it is board range
        {
            if(turn==1)
                turn=2; // switch turn
            else if(turn==2)
                turn=1; // switch turn
        }
        if(x>900 && x<975 && y>100 && y<150 && undo==false) // if it is board range
        {
            for(int i=0; i<8; i++) // for all board
            {
                for(int f=0; f<8; f++) // for all board
                {
                    disks[i][f]=undodisks[i][f];
                }
            }
            if(turn==1)
                turn=2; // switch turn
            else if(turn==2)
                turn=1; // switch turn
            initi--;
            clickx=clickx1; // change the highlight circle
            clicky=clicky1; // change the highlight circle
            cout<<clickx<<","<<clicky<<endl;
            cout<<initi<<endl;
            black=black1;
            white=white1;
            whitewin=false; // undo surrender
            blackwin=false; // undo surrender
            win=false; // undo win
            undo=true;
            ok=true;
        }
        if(x>900 && x<975 && y>850 && y<900) // if it is board range
        {
            exit(0);
        }
        if(x>890 && x<995 && y>600 && y<650) // if it is board range
        {
            if(turn==2)
                whitewin=true; // white wins
            else if(turn==1)
                blackwin=true; // black wins
        }
    }
    glutPostRedisplay(); // redisplay
}

void initGL()
{
    glClearColor(0,0,10,1);//blue background
}

void Board(void) // draw board
{
    const int font = (int)GLUT_BITMAP_TIMES_ROMAN_24; // change font
    glClearColor(0,0,10,1);//blue background
    glClear(GL_COLOR_BUFFER_BIT);// clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // the default identity matrix
    gluOrtho2D(0.0, 20.0, 0.0, 20.0); // resize dimension
    glMatrixMode(GL_MODELVIEW); // set the current matrix to the modelview matrix stack
    for(int i=0; i<=8; i++) // draw lines with for loop
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0); // yellow
        glVertex2f(i*2+1, 2.0); // a dot
        glVertex2f(i*2+1, 18.0); // other end of line
        glEnd();
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0); // yellow
        glVertex2f(1.0,i*2+2); // a dot
        glVertex2f(17.0,i*2+2); // other end of line
        glEnd();
    }
    if(initi>0)
    {
        glBegin(GL_POLYGON); // rectangle
        glColor3f(1.0, 1.0, 0.0); // yellow
        glVertex2f(19.5,17);
        glVertex2f(18, 17);
        glVertex2f(18, 18);
        glVertex2f(19.5, 18);
        glEnd();
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(18.2, 17.35, (void *)font, "Undo"); // display text
        drawFilledCircleY((clickx+1)*2, 17-clicky*2, 0.8);
    glBegin(GL_POLYGON); // rectangle
    glColor3f(1.0, 1.0, 0.0); // yellow
    glVertex2f(19.9,7);
    glVertex2f(17.8, 7);
    glVertex2f(17.8, 8);
    glVertex2f(19.9,8);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(17.9, 7.35, (void *)font, "Surrender"); // display text
    }
    glBegin(GL_POLYGON); // rectangle
    glColor3f(1.0, 1.0, 0.0); // yellow
    glVertex2f(19.5,15);
    glVertex2f(18, 15);
    glVertex2f(18, 16);
    glVertex2f(19.5, 16);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(18.2, 15.35, (void *)font, "Pass"); // display text
    glBegin(GL_POLYGON); // rectangle
    glColor3f(1.0, 1.0, 0.0); // yellow
    glVertex2f(19.5,2);
    glVertex2f(18, 2);
    glVertex2f(18, 3);
    glVertex2f(19.5,3);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(18.2, 2.35, (void *)font, "Quit"); // display text
    for (int i=0; i<8; i++) // for all board
    {
        for(int f=0; f<8; f++) // for all board
        {
            if (disks[i][f]==1) // if there is black
                drawFilledCircleB((i+1)*2, 17-f*2, 0.75); // draw black circle
            if (disks[i][f]==2) // if there is white
                drawFilledCircle((i+1)*2, 17-f*2, 0.75); // draw white circle
        }
    }
    if(ok==false) // if move is invalid
    {
        glColor3f(1.0, 0.0, 0.0); // red
        renderBitmapString(4.25, 18.5, (void *)font, "Invalid Move"); // print invalid move
    }
    if(initi>0)
    {
        if(black==0 || blackwin==true)
        {
            glColor3f(1.0, 1.0, 1.0); // white
            renderBitmapString(10, 18.5, (void *)font, "White wins"); // display result
            win=true;
        }
        if(white==0 || whitewin==true)
        {
            glColor3f(0.0, 0.0, 0.0);// b
            renderBitmapString(10, 18.5, (void *)font, "Black wins"); // display result
            win=true;
        }
    }
    if(white+black==64)
    {
        if(white>black)
        {
            glColor3f(1.0, 1.0, 1.0); // white
            renderBitmapString(10, 18.5, (void *)font, "White wins"); // display result
            win=true;
        }
        else if (black>white)
        {
            glColor3f(0.0, 0.0, 0.0);// b
            renderBitmapString(10, 18.5, (void *)font, "Black wins"); // display result
            win=true;
        }
        else if (black==white)
        {
            glColor3f(1.0, 0.0, 0.0);// b
            renderBitmapString(10, 18.5, (void *)font, "Tie"); // display result
            win=true;
        }
    }
    if(turn==1 && win==false) // if it is black turn
    {
        glColor3f(0.0, 0.0, 0.0); // b
        renderBitmapString(7, 18.5, (void *)font, "Black's turn"); // display turn
    }
    if(turn==2 && win==false)
    {
        glColor3f(1.0, 1.0, 1.0); // white
        renderBitmapString(7, 18.5, (void *)font, "White's turn"); // display turn
    }
    char buffer[256]; // character for current status
    sprintf(buffer,"%d", white); // change int to char
    char buffer1[256]; // character for current status
    sprintf(buffer1,"%d", black); // change int to char
    glColor3f(1.0, 1.0, 1.0);  // white
    renderBitmapString(8, 1, (void *)font, "White x"); // display current
    renderBitmapString(9.7, 1, (void *)font, buffer); // display current
    glColor3f(0.0, 0.0, 0.0); // black
    renderBitmapString(3, 1, (void *)font, "Black x"); // display current
    renderBitmapString(4.7, 1, (void *)font, buffer1); // display current
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
    cout<<"drawn\n";
}


int main(int argc, char** argv)
{
    int aaaa=0; // initial setup
    if(aaaa==0) // initial setup
    {
        for(int i=0; i<8; i++)
        {
            for(int f=0; f<8; f++)
            {
                disks[i][f]=0; // initial setup of the array

            }
        }
        disks[3][3]=1; // initial board setup
        disks[3][4]=2; // initial board setup
        disks[4][3]=2; // initial board setup
        disks[4][4]=1; // initial board setup
        for(int i=0; i<8; i++)
        {
            for(int f=0; f<8; f++)
            {
                undodisks[i][f]=disks[i][f]; // initial setup of the array for undo

            }
        }
        aaaa=1;
        turn=1;
    }
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,1000); // size
    win1=glutCreateWindow("Reversi"); // title
    initGL();
    glutDisplayFunc(Board); // display func
    glutMouseFunc(OnMouseClick); // mouse click func
    glutKeyboardFunc(keyPressed); // keyboard func
    glutMainLoop();
    return 0;
}
