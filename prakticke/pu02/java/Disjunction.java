package com.company;

import java.util.Map;
import java.util.Set;

public class Disjunction extends Formula {

    protected Formula[] disjunctions;

    public Disjunction(Formula[] disjuncts){
        this.disjunctions = disjuncts;

        for(Formula f : disjuncts){
            for(String s : f.vars())
                setOfVariables.add(s);
        }
    }


    public Formula substitute(Formula what, Formula replacement){
        Formula[] newFromula = disjunctions;
        for(int i = 0 ; i < newFromula.length ; i++){
            if(newFromula[i].equals(what)){
                newFromula[i] = replacement;
            }else{
                newFromula[i] = newFromula[i].substitute(what, replacement);
            }
        }
        Formula result = new Disjunction(newFromula);
        return result;
    }


    public String toString(){
        String result = "";
        for(int i = 0; i < disjunctions.length; i++)
            result += disjunctions[i] + "|";
        return "(" + result.substring(0 , result.length() - 1) + ")" ;
}

    public int deg(){
        int result = 1;
        for(int i = 0; i < disjunctions.length; i++)
            result += disjunctions[i].deg();
        return result;
    }

    public boolean equals(Formula other){
        return (toString().equals(other.toString()));
    }



    public boolean isSatisfied( Map<String, Boolean> v){
        for(int i = 0; i < disjunctions.length; i++){
            if(disjunctions[i].isSatisfied(v))
                return true;
        }
        return false;
    }

    public Formula[]  subf(){
        return disjunctions;
    }




}