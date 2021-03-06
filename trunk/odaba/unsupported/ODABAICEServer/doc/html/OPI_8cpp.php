<? include "layout/head.inc.php";?>
<!-- Generated by Doxygen 1.4.6 -->
<div class="tabs">
  <ul>
    <li><a href="index.php"><span>Main&nbsp;Page</span></a></li>
    <li><a href="namespaces.php"><span>Namespaces</span></a></li>
    <li><a href="annotated.php"><span>Classes</span></a></li>
    <li id="current"><a href="files.php"><span>Files</span></a></li>
  </ul></div>
<div class="tabs">
  <ul>
    <li><a href="files.php"><span>File&nbsp;List</span></a></li>
    <li><a href="globals.php"><span>File&nbsp;Members</span></a></li>
  </ul></div>
<h1>OPI.cpp File Reference</h1><h2>Namespaces</h2>
<ul>
<li>namespace <a class="el" href="namespaceOPI.php">OPI</a>
</ul>
<h2>Classes</h2>
<ul>
<li>class <a class="el" href="classOPI_1_1CheckOptions.php">OPI::CheckOptions</a>
<li>class <a class="el" href="classOPI_1_1DBObjectHandle.php">OPI::DBObjectHandle</a>
<li>class <a class="el" href="classOPI_1_1DataSourceHandle.php">OPI::DataSourceHandle</a>
<li>class <a class="el" href="classOPI_1_1DBObjectHandle.php">OPI::DBObjectHandle</a>
<li>class <a class="el" href="classOPI_1_1DatabaseHandle.php">OPI::DatabaseHandle</a>
<li>class <a class="el" href="classOPI_1_1ODABAClient.php">OPI::ODABAClient</a>
<li>class <a class="el" href="classOPI_1_1OperationHandle.php">OPI::OperationHandle</a>
<li>class <a class="el" href="classOPI_1_1PropertyHandle.php">OPI::PropertyHandle</a>
<li>class <a class="el" href="classOPI_1_1OPIFactory.php">OPI::OPIFactory</a>
<li>class <a class="el" href="classOPI_1_1Session.php">OPI::Session</a>
<li>class <a class="el" href="classOPI_1_1SessionFactory.php">OPI::SessionFactory</a>
</ul>
<h2>Enumerations</h2>
<ul>
<li>enum <a class="el" href="namespaceOPI.php#b6145b86cfe58a7bd071b8a4e538401c">OPI::PIACC</a> { <a class="el" href="namespaceOPI.php#b6145b86cfe58a7bd071b8a4e538401c041a6ceaf6e131bfcca0b329d61a51ab">OPI::piaREAD</a>, 
<a class="el" href="namespaceOPI.php#b6145b86cfe58a7bd071b8a4e538401c353bf6e9c5e548c375a38878be0be112">OPI::piaWRITE</a>, 
<a class="el" href="namespaceOPI.php#b6145b86cfe58a7bd071b8a4e538401c6e0407127137221e18171015dfe4b1ad">OPI::piaUPDATE</a>, 
<a class="el" href="namespaceOPI.php#b6145b86cfe58a7bd071b8a4e538401c906b4584a9b3f5bd339fea698c5cca6a">OPI::piaUNDEFINED</a>
 }
<li>enum <a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf">OPI::PIREPL</a> { <br>
&nbsp;&nbsp;<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf4a469d4d7920735fc715784cf13170c4">OPI::piaREPLGUID</a>, 
<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf77f4f252f28b8642d8ab8c2f24af1ef8">OPI::piaREPLDIRECT</a>, 
<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bfc4f2d3fd96fdc900a039e62b3b1f61a9">OPI::piaREPLNONE</a>, 
<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf8da049eb7e3f4a27ee094560398bca78">OPI::piaREPLLOCAL</a>, 
<br>
&nbsp;&nbsp;<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf1ab7adc4be55661303a87acccbe47654">OPI::piaREPLALL</a>, 
<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf417ed6c1bb6de057d3231c1244a3a1e9">OPI::piaREPLINSTANCE</a>, 
<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf740df5595a3907753b87051fc6f7bd96">OPI::piaREPLRELATIONSHIPS</a>, 
<a class="el" href="namespaceOPI.php#a609ba1fa786f53c52e72cfe3417a5bf24ea37b4fd3393889f3f19cc6eea20dd">OPI::piaREPLNOCREATE</a>
<br>
 }
<li>enum <a class="el" href="namespaceOPI.php#289d71610e1123a19421638a59be5a04">OPI::PIADEF</a> { <a class="el" href="namespaceOPI.php#289d71610e1123a19421638a59be5a0433845fbd41dea18011f5c02a5e8e42a5">OPI::piaUNKNOWN</a>, 
<a class="el" href="namespaceOPI.php#289d71610e1123a19421638a59be5a04b51b0f3c6beaef68e06a0327b5e47b62">OPI::piaEXCLUSIVE</a>, 
<a class="el" href="namespaceOPI.php#289d71610e1123a19421638a59be5a04eeea872de7ed970fa35d2c5a17faebd5">OPI::piaSHARE</a>
 }
<li>enum <a class="el" href="namespaceOPI.php#f99d2362cb8ceeee7f89f4d7484cac08">OPI::ResourceTypes</a> { <a class="el" href="namespaceOPI.php#f99d2362cb8ceeee7f89f4d7484cac0807129435e6c3683a127a7464d82f70dd">OPI::resAUTOMATIC</a>, 
<a class="el" href="namespaceOPI.php#f99d2362cb8ceeee7f89f4d7484cac08e32e8bb68f1facd68517d9c15235753b">OPI::resSERVER</a>, 
<a class="el" href="namespaceOPI.php#f99d2362cb8ceeee7f89f4d7484cac082b27f61adf8e23957c089f469567e013">OPI::resLOCAL</a>, 
<a class="el" href="namespaceOPI.php#f99d2362cb8ceeee7f89f4d7484cac08700d43b8cb141e238b6095d7a2162f5f">OPI::resSERVERINTERN</a>
 }
<li>enum <a class="el" href="namespaceOPI.php#404bdda975fb800f7c6400da4d6a2a52">OPI::ApplicationTypes</a> { <a class="el" href="namespaceOPI.php#404bdda975fb800f7c6400da4d6a2a52ef2c717bea5f5cc4e06bca6f9b355a37">OPI::aptWINDOWS</a>, 
<a class="el" href="namespaceOPI.php#404bdda975fb800f7c6400da4d6a2a5214ff0a6c61856a53698159fc902b5694">OPI::aptCONSOLE</a>
 }
</ul>
<? include "layout/foot.inc.php";?>
