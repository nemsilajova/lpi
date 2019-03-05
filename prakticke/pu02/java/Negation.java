package com.company;

import java.util.Map;
import java.util.Set;

public class Negation extends Formula {
    protected Formula original;


    public Negation(Formula originalFormul){
        this.original = originalFormul;

        for(String s : original.vars())
            setOfVariables.add(s);

    }

    public  Formula originalFormula(){
        return original;
    }


    public Formula substitute(Formula what, Formula replacement){
        Formula newFormula = original;

        newFormula = newFormula.substitute(what , replacement);

        Formula result = new Negation(newFormula);
        return result;
    }


    public String toString(){
        return "-" + original;
    }

    public int deg(){
        return  1 + original.deg();
    }


    public boolean equals(Formula other){
        return toString().equals(other.toString());
    }



    public boolean isSatisfied( Map<String, Boolean> v){
        if (original.isSatisfied(v)){
            return false;
        }
        return true;
    }


    public Formula[]  subf(){
        return new Formula[]{original};
    }



}
