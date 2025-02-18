var name = "hello";
console.log(name);
console.log();

//for loop
let car = [1,2,3];
for (let i=0;i<car.length;i++){
    console.log(car[i]);
}
console.log();

//forEach loop
car.forEach(
    car=>{console.log(car);}
);
console.log();

//functions in JS
function outfun(x){
    let y=8;
    function infun(){
        console.log(x+y);
    }
    return infun;
}
const number=outfun(5);
number();

