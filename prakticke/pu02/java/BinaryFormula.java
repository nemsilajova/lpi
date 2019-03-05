package com.company;

import java.util.Set;

public class BinaryFormula extends Formula {

    protected Formula leftSide;
    protected Formula rightSide;

    public BinaryFormula(Formula leftSide, Formula rightSide){
        this.leftSide = leftSide;
        this.rightSide = rightSide;

        for(String s : leftSide.vars())
            setOfVariables.add(s);
        for(String s : rightSide.vars())
            setOfVariables.add(s);
    }



    public Formula leftSide() {
        return leftSide;
    }

    public Formula rightSide() {
        return rightSide;
    }



    public int deg(){
        int result = 1 + leftSide.deg() + rightSide.deg();
        return result;
    }


    public boolean equals(Formula other){
        return toString().equals(other.toString());
    }



    public Formula[]  subf(){
        Formula[] formulas = {leftSide() , rightSide()};
        return formulas;
    }


}