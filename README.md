# powershell alias

1. powershell 프로필 열기
   ```powershell
   code $PROFILE
   ```
2. `solve` alias 추가하기

   ```ps1
    function solve {
        # 1. 로컬 변경 사항 커밋
        git add -A;
        git commit -m "solve";

        # 2. 원격 저장소 변경 사항 자동 병합 (Rebase 방식)
        Write-Host "🔄 원격 저장소와 동기화 중..." -ForegroundColor Cyan
        git pull --rebase origin main;

        # 3. Pull 결과 확인 (충돌 발생 여부)
        if ($LASTEXITCODE -ne 0) {
            Write-Host "❌ [오류] 자동 병합 중 충돌이 발생했습니다!" -ForegroundColor Red
            Write-Host "👉 에러가 난 파일을 열어 충돌을 해결한 후, 다음 명령어를 순서대로 입력하세요:" -ForegroundColor Yellow
            Write-Host "   1. git add 변경한파일"
            Write-Host "   2. git rebase --continue"
            Write-Host "   3. git push origin main"
            return
        }

        # 4. 충돌이 없으면 푸시 진행
        Write-Host "🚀 원격 저장소로 푸시합니다..." -ForegroundColor Cyan
        git push origin main;
    }
   ```

3. 만약 한글 깨짐이 생기면
   - vscode에서 $PROFILE 열기
   - vscode 우측 하단 `UTF-8` 클릭
   - `save with encoding` 선택
   - `UTF-8 with BOM`으로 다시 저장하기
   - powershell 재시작

# bash alias

1. bashrc 열기
   ```bash
   code ~/.bashrc
   ```
2. `solve` alias 추가하기

   ```bash
    function solve() {
        # 1. 로컬 변경 사항 커밋
        git add -A
        git commit -m "solve"

        # 2. 원격 저장소 변경 사항 자동 병합 (Rebase 방식)
        echo -e "\033[36m🔄 원격 저장소와 동기화 중...\033[0m"
        git pull --rebase origin main

        # 3. Pull 결과 확인 (충돌 발생 여부)
        if [ $? -ne 0 ]; then
            echo -e "\033[31m❌ [오류] 자동 병합 중 충돌이 발생했습니다!\033[0m"
            echo -e "\033[33m👉 에러가 난 파일을 열어 충돌을 해결한 후, 다음 명령어를 순서대로 입력하세요:\033[0m"
            echo "   1. git add 변경한파일"
            echo "   2. git rebase --continue"
            echo "   3. git push origin main"
            return 1
        fi

        # 4. 충돌이 없으면 푸시 진행
        echo -e "\033[36m🚀 원격 저장소로 푸시합니다...\033[0m"
        git push origin main
    }
   ```
