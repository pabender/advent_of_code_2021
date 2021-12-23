package com.nscaleintermodal;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.*;
import java.util.stream.Collectors;

public class Day22Part1 {

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

    public Day22Part1(String fileName){
        List<String> lines;

        File f =  new File(fileName);
        try {
            BufferedReader reader = new BufferedReader(new FileReader(f));
            lines = reader.lines().collect(Collectors.toList());
        } catch(java.io.FileNotFoundException fnfe) {
            lines = new ArrayList<>();
        }

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

            if( xmin<-50 || xmax>50 || ymin<-50 || ymax >50 || zmin<-50 || zmax>50) continue;

            for(int x=xmin;x<=xmax;x++) {
                for(int y=ymin;y<=ymax;y++){
                    for(int z=zmin;z<=zmax;z++){
                        if(add){
                            pointSet.add(new Point(x,y,z));
                        } else {
                            pointSet.remove(new Point(x,y,z));
                        }
                    }
                }

            }

        }

    }

    private Set<Point> pointSet=new HashSet<>();

    public void addPointToSet(Point p){
        pointSet.add(p);
    }

    public void removePointFromSet(Point p){
        if(pointSet.contains(p)){
            pointSet.remove(p);
        }
    }

    public double getPathCount() {
        return pointSet.size();
    }
}
