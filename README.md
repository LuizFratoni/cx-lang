# cx-lang
www.cx-lang.com

A Front-End to LVVM to Compile an Extend C Based Language.
CX is an Oriented Object Language with Moderns Languages features.


``` c
int multi(a, b){
  return a * b;
}

int main(String[] args){ //could be [String] args
  return multi(10, 20);
  ///
  return multi( b: 20, a : 30);
}
```

### CX BULK Methods (Cx Queries)
plain C
```c
for (int i = 0; i < personsCount; i++){
  if (strcmp("PersonName", persons[i].name) == 0)
     return person;
}

```

CX
````c
Person p = persons[ name == "luiz" ]
````


UPDATE CONTENT (Using the STREAMS OPERATOR IN C++)
````c++
myPerson << { name : "luiz", lastname : "fratoni", email : "luizfratoni@gmail.com" }
persons[20] << { name : "luiz", lastname : "fratoni", email : "luizfratoni@gmail.com" }
persons[ id == 30 ] << { ... }

persons[ age > 18] << { adult : true }
````


QUERIES (Using the STREAMS OPERATOR IN C++)
```````c++
  var data << persons[1..15] { name, lastName, phones [ active == true] { phoneNumber, prefix } }
  
  var data << persons[ name startsWith "a%" ] { name, lastName, phones [ active == true] { phoneNumber, prefix } }

  var data << person[ birthday == today | max(15) order(name asc)   ] 
  
  var newDict = { 
    veiculo : os.placa + “ - “ + os.marca,
    Valor : os.2000,
    double total : 0, 
 } from os [status == “OF”]

 var listOS << os[1,2,3,4,5,10,15,23];


``````
RELATIONAL QUERIES
```````c++

var result := {
     id : o.id, 
     customer : c.name,
     vehicle : v.vehicle + " " + v.model
} from orders(o) left join customers(c) 
  where o.status == 'OF' && c.active == true


``````