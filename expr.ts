defineAst("Expr", [
  "Binary   | Expr left, Token _operator, Expr right",
  "Grouping | Expr expression",
  "Literal  | std::string value",
  "Unary    | Token _operator, Expr right"
])

function defineAst(baseName: string, types: string[]) {
  console.log("#include \"token.hpp\"\n#include <string>\n");
  console.log(`class ${baseName} {};\n`);

  types.forEach((element) => {
    const className = element.split("|")[0].trim();
    const fields = element.split("|")[1].trim();
    defineType(baseName, className, fields);
  });

}

function defineType(baseName: string, className: string, fieldList: string) {
  console.log(`class ${className} : protected ${baseName} {`);

  console.log(`  ${className}(${fieldList}) {`);

  const fields = fieldList.split(", ");
  fields.forEach((element) => {
    const name = element.split(" ")[1];
    console.log(`    this->${name} = ${name};`);
  });

  console.log("  }\n");

  fields.forEach((element) => {
    console.log(`  ${element};`);
  });

  console.log("};\n");
}