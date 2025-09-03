#!/usr/bin/bash

cppcheck --enable=all \
    --inline-suppr \
    --project="${BUILD_DIR:-build}"/compile_commands.json \
    -i"${BUILD_DIR:-build}" --suppress="*:${BUILD_DIR:-build}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    -i"${GEN_DIR:-generated}" --suppress="*:${GEN_DIR:-generated}/*" \
    --suppress=missingIncludeSystem \
    --suppress=missingInclude \
    --suppress=unmatchedSuppression \
    --suppress=useStlAlgorithm \
    --suppress=unusedFunction \
    --suppress=cstyleCast \
    --suppress=noExplicitConstructor \
    --suppress=unusedStructMember \
    --suppress=functionStatic \
    --suppress=noConstructor \
    --suppress=knownConditionTrueFalse \
    --suppress=passedByValue \
    --suppress=passedByValueCallback \
    --suppress=returnByReference \
    --suppress=useInitializationList \
    --suppress=constVariablePointer \
    --suppress=uninitMemberVarPrivate \
    --suppress=constParameterReference \
    --suppress=normalCheckLevelMaxBranches \
    --error-exitcode=1
