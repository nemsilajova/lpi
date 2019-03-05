package com.company;

import java.util.Map;

public class Implication extends BinaryFormula {


    public Implication(Formula f1 , Formula f2){
        super( f1 ,  f2);
    }

    public String toString() {
        return "(" + leftSide + "->" + rightSide + ")";
    }


    public boolean isSatisfied( Map<String, Boolean> v){
        if(!leftSide.isSatisfied(v) || rightSide.isSatisfied(v))
            return true;
        return false;
    }


    public Formula substitute(Formula what, Formula replacement){
        Formula left = leftSide;
        Formula right = rightSide;

        if(left.equals(what)){
            left = replacement;
        }
        else{
            left = left.substitute(what, replacement);
        }

        if(right.equals(what)){
            right = replacement;
        }
        else{
            right = right.substitute(what, replacement);
        }


        Formula result = new Implication(left , right);
        return result;
    }






}
