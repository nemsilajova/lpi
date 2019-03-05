package com.company;
import java.util.*;

public class Formula {
    protected Set<String> setOfVariables = new HashSet<String>();

    public Formula() {

    }

    public Formula[]  subf(){
        Formula[] result = new Formula[0];
        return result;
    }

    public String toString(){
        return "";
    }

    public boolean isSatisfied( Map<String, Boolean> v){
        return false;
    }


    public boolean equals(Formula other){
        return false;
    }


    public int deg(){
        return 0;
    }


    public Set<String> vars(){
        return setOfVariables ;
    }


    public Formula substitute(Formula what, Formula replacement){
        Formula newFormula =  new Formula();

        return newFormula;
    }



}

