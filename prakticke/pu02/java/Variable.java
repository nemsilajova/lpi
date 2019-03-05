package com.company;
import java.util.Map;
import java.util.Set;

public class Variable extends Formula {
    private String name = "";


    public Variable(String name){
        this.name = name;
        setOfVariables.add(name);

    }


    public String name(){
        return this.name;
    }


    public Formula substitute(Formula what, Formula replacement){
        String tmp = "";

        if(toString().equals(what.toString())){
            tmp = replacement.toString();
        }else{
            tmp = this.name;
        }
        Formula newFormula =  new Variable(tmp);
        return newFormula;
    }



    public String toString() {
        return this.name;
    }

    public int deg(){
        return 0;
    }

    public boolean equals(Variable other){
        return this.name.equals(other.name());
    }



    public boolean isSatisfied( Map<String, Boolean> v){
        return v.get(name);
    }





}
