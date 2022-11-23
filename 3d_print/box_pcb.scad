/*Customizer Variables*/
height=120;//[5:1:100]
width=110;//[5:1:100]
depth=35;//[5:1:100]
wall=10;//[0.5:0.2:5]
tollerance=1.2;//[0.5:0.2:5]
screw_r= 1.5;


module base()
{   difference()
    {
        union()
        {
            difference()
            {
               union()
                {
                    cube([height+2*wall,width+2*wall,depth+wall]);
                    //translate([-wall,-wall,depth]) cube([height+4*wall,width+4*wall,wall]);
                    //translate([wall,wall,wall])cube([height,width,depth]);
                
                }   
                
                
                translate([wall,wall,wall])cube([height,width,depth]);
                
                
                
                
            }
        
        translate([wall+10,wall+10,wall])
                    cylinder(6,6,6);
        translate([wall+height-10,wall+10,wall])
                    cylinder(6,6,6);
        translate([wall+height-10,wall+width-10,wall])
                    cylinder(6,6,6);
        translate([wall+10,wall+width-10,wall])
                    cylinder(6,6,6);
        
        }
        // place for holes
        
        translate([wall/2,wall/2,depth-10])
            cylinder(200,screw_r,screw_r);
        translate([wall+height+wall/2,wall/2,depth-10])
            cylinder(200,screw_r,screw_r);
        translate([wall/2,wall/2+width+wall,depth-10])
            cylinder(200,screw_r,screw_r);
        translate([wall/2+wall+height,wall/2+wall+width,depth-10])
            cylinder(200,screw_r,screw_r);
        
        translate([wall+10,wall+10,0])
            cylinder(200,screw_r,screw_r);
        translate([wall+height-10,wall+10,0])
            cylinder(200,screw_r,screw_r);
        
        translate([0,wall+10,wall+6])
            cube([wall,40,depth]);
        translate([wall+70,0,wall+16])
            cube([40,wall,depth]);
    }
}
module cover()
{  
   difference(){
    cube([height+wall*2,width+wall*2,wall]);
    translate([wall/2,wall/2,0])
        cylinder(200,screw_r,screw_r);
    translate([wall+height+wall/2,wall/2,0])
        cylinder(200,screw_r,screw_r);
    translate([wall/2,wall/2+width+wall,0])
        cylinder(200,screw_r,screw_r);
    translate([wall/2+wall+height,wall/2+wall+width,0])   
       cylinder(200,screw_r,screw_r);
   } 
}
render()base();
translate([height+wall*2+10,0,0])
render()cover();
