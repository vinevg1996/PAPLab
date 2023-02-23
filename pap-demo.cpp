/*
 * Copyright 2021 Jan Peleska, Moritz Bergenthal, Robert Sachtleben, Niklas Krafczyk
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cassert>
#include <string>

#include "libfsmtest.hpp"

using namespace std;
using namespace libfsmtest;

#ifndef RESOURCEPATH_PAP
#define RESOURCEPATH_PAP string("../../pap-resources/")
#endif


static void demo_csvInput() {

    FsmPtr fsm = createFsm<FsmFromFileCreator>(RESOURCEPATH_PAP+"garage-door-controller2.csv",
                                                        "garage-door-controller2",
                                                        make_unique<ToAutoCompleteWithSelfLoopTransformer>(nullptr, "null"));
    
    ToDotFileVisitor dot("garage-door-controller2.dot");
    fsm->accept(dot);
    dot.writeToFile();
    
    /*
    size_t numAddStates = 1;
    TestGenerationFrame<WPMethod> genFrame("SUITE-GDC-WP", move(fsm), numAddStates);
    
    genFrame.generateTestSuite();
    genFrame.writeToFile();
    */
    
}

static void demo_csvInput_pap() {

    FsmPtr fsm = createFsm<FsmFromFileCreator>(RESOURCEPATH_PAP+"pap3_lib.csv",
                                                        "pap3_lib",
                                                        make_unique<ToAutoCompleteWithSelfLoopTransformer>(nullptr, "null"));
    
    ToDotFileVisitor dot("pap3_lib.dot");
    fsm->accept(dot);
    dot.writeToFile();
    
    // Create the test generation framework with the W-Method
    size_t numAddStates = 0;
    TestGenerationFrame<WMethod> genFrame("SUITE-W-3", move(fsm), numAddStates);
    
    // Generate the test suite and write it to file
    genFrame.generateTestSuite();
    genFrame.writeToFile();
        
}

int main(int, char** ) {
    cout << "Usage demo for the libfsmtest " << version.major << "." << version.minor << endl;
    
    //demo_csvInput();
    
    demo_csvInput_pap();

    return 0;
}
