package com.company;

import java.util.Map;
import java.util.Set;

public class Conjunction extends Formula {

    protected Formula[] conjunctions;

    public Conjunction(Formula[] conjuncts){
        this.conjunctions = conjuncts;

        for(Formula f : conjunctions){
            for(String s : f.vars())
                setOfVariables.add(s);
        }
    }




    public Formula substitute(Formula what, Formula replacement){
        Formula[] newFromula = conjunctions;
        for(int i = 0 ; i < newFromula.length ; i++){
            if(newFromula[i].equals( what)){
                newFromula[i] = replacement;
            }else{
                newFromula[i] = newFromula[i].substitute(what , replacement);
            }
        }
        Formula newFormula =  new Conjunction(newFromula);

        return newFormula;
    }


    public String toString(){
        String result = "";
        for(int i = 0; i < conjunctions.length; i++)
            result += conjunctions[i] + "&";
        return "(" + result.substring(0 , result.length() - 1) + ")";
    }


    public int deg(){
        int result = 1;
        for(int i = 0; i < conjunctions.length; i++)
            result += conjunctions[i].deg();
        return result;
    }


    public boolean equals(Formula other){
        return (toString().equals(other.toString()));
    }



    public boolean isSatisfied( Map<String, Boolean> v){
        for(int i = 0; i < conjunctions.length; i++){
            if(!conjunctions[i].isSatisfied(v))
                return false;
        }
        return true;
    }


    public Formula[]  subf(){
        return conjunctions;
    }

}

