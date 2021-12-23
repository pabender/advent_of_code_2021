package com.nscaleintermodal;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.*;
import java.util.stream.Collectors;

public class Day22Part2 {

    private static class Point {
        int x,y,z;
        Point(int x, int y, int z){
            this.x=x;
            this.y=y;
            this.z=z;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public int getZ() {
            return z;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Point point = (Point) o;
            return x == point.x &&
                    y == point.y &&
                    z == point.z;
        }

        @Override
        public int hashCode() {
            return Objects.hash(x, y, z);
        }

        @Override
        public String toString() {
            return "Point{" +
                    "x=" + x +
                    ", y=" + y +
                    ", z=" + z +
                    '}';
        }
    }

    private class grid{
        private boolean on;
        private int xmin,xmax,ymin,ymax,zmin,zmax;
        private grid(boolean on,int xmin,int xmax,int ymin,int ymax,int zmin, int zmax){
            this.on=on;
            this.xmin=xmin;
            this.xmax=xmax;
            this.ymin=ymin;
            this.ymax=ymax;
            this.zmax=zmax;
            this.zmin=zmin;
        }

        boolean isOn(){
            return on;
        }

        boolean contains(Point p){
            return xmin <= p.x && xmax>= p.x && ymin <= p.y && ymax >= p.y && zmin <= p.z && zmax >= p.z;
        }
    }

    List<grid> grids = new ArrayList<>();
    int uxmin=0,uxmax=0,uymin=0,uymax=0,uzmin=0,uzmax=0;

    public Day22Part2(String fileName){
        List<String> lines;

        File f =  new File(fileName);
        try {
            BufferedReader reader = new BufferedReader(new FileReader(f));
            lines = reader.lines().collect(Collectors.toList());
        } catch(java.io.FileNotFoundException fnfe) {
            lines = new ArrayList<>();
        }

        boolean initialSet=false;

        for(String line:lines) {
            boolean add = line.startsWith("on");
            int position1=line.indexOf('=');
            int position2=line.indexOf("..");
            int xmin=Integer.valueOf(line.substring(position1+1,position2));
            int position3=line.indexOf(",");
            int xmax=Integer.valueOf(line.substring(position2+2,position3));
            String remaining = line.substring(position3+1);
            position1=remaining.indexOf('=');
            position2=remaining.indexOf("..");
            int ymin=Integer.valueOf(remaining.substring(position1+1,position2));
            position3=remaining.indexOf(",");
            int ymax=Integer.valueOf(remaining.substring(position2+2,position3));
            remaining = remaining.substring(position3+1);
            position1=remaining.indexOf('=');
            position2=remaining.indexOf("..");
            int zmin=Integer.valueOf(remaining.substring(position1+1,position2));
            int zmax=Integer.valueOf(remaining.substring(position2+2));

            System.out.println("x " + xmin + " " +xmax + " y " +ymin +" " +ymax + " z " +zmin + " " +zmax);

            grids.add(0,new grid(add,xmin,xmax,ymin,ymax,zmin,zmax));

            if(!initialSet){
                uxmax = xmax;
                uxmin = xmin;
                uymax = ymax;
                uymin = ymin;
                uzmax = zmax;
                uzmin = zmin;
                initialSet=true;
            }

            if(uxmin>xmin) {
              uxmin=xmin;
            }
            if(uxmax<xmax) {
                uxmax=xmax;
            }
            if(uymin>ymin) {
                uymin=ymin;
            }
            if(uymax<ymax) {
                uymax=ymax;
            }
            if(uzmin>zmin) {
                uzmin=zmin;
            }
            if(uzmax<zmax) {
                uzmax=zmax;
            }


        }

    }


    public double getCount() {
        double count = 0;
        for(int x=uxmin;x<=uxmax;x++) {
            for(int y=uymin;y<=uymax;y++){
                for(int z=uzmin;z<=uzmax;z++){
                    for( grid g:grids) {
                       if(g.contains(new Point(x,y,z))){
                          if(g.isOn()){
                              count+=1;
                           }
                           break;
                        }
                    }
                }
            }

        }
        return count;
    }
}
