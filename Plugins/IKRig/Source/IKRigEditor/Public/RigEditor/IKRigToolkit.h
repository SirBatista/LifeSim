// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "IHasPersonaToolkit.h"
#include "IKRigController.h"
#include "IKRigEditorController.h"
#include "IKRigMode.h"
#include "IPersonaPreviewScene.h"
#include "PersonaAssetEditorToolkit.h"
#include "SIKRigSkeleton.h"

class IAnimationSequenceBrowser;
class UIKRigSkeletalMeshComponent;
class FSolverStackElement;
class SIKRigSolverStack;
class SIKRigSkeleton;
class FIKRigSkeletonTreeBuilder;
class IDetailsView;
class ISkeletonTree;
class FGGAssetEditorToolbar;
class UIKRigDefinition;
class UIKRigSettings;
class FIKRigToolbar;
class SIKRigViewportTabBody;
class FIKRigPreviewScene;

namespace IKRigEditorModes
{
	extern const FName IKRigEditorMode;
}

class FIKRigEditorToolkit :
	public FPersonaAssetEditorToolkit,
	public IHasPersonaToolkit,
	public FGCObject,
	public FSelfRegisteringEditorUndoClient,
	public FTickableEditorObject
{
public:

	FIKRigEditorToolkit();
	virtual ~FIKRigEditorToolkit() override;

	void InitAssetEditor(
		const EToolkitMode::Type Mode,
		const TSharedPtr< IToolkitHost >& InitToolkitHost,
		UIKRigDefinition* IKRigAsset);

	/** FAssetEditorToolkit interface */
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	/** END FAssetEditorToolkit interface */
	
	/** FGCObject interface */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("FIKRigEditorToolkit");
	}
	/** END FGCObject interface */

	//** FTickableEditorObject Interface
	virtual void Tick(float DeltaTime) override {};
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
	virtual TStatId GetStatId() const override;
	//~ END FTickableEditorObject Interface

	/** IHasPersonaToolkit interface */
	virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override { return PersonaToolkit.ToSharedRef(); }
	/** END IHasPersonaToolkit interface */

	/** FSelfRegisteringEditorUndoClient interface */
	virtual void PostUndo( bool bSuccess );
	virtual void PostRedo( bool bSuccess );
	/** END FSelfRegisteringEditorUndoClient interface */

	TSharedRef<FIKRigEditorController> GetController() const {return EditorController;};

private:

	/** toolbar */
	void BindCommands();
	void ExtendToolbar();
	void FillToolbar(FToolBarBuilder& ToolbarBuilder);
	void HandleReset();
	/** END toolbar */
	
	/** preview scene setup */
	void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);
	void HandlePreviewMeshChanged(USkeletalMesh* InOldSkeletalMesh, USkeletalMesh* InNewSkeletalMesh);
	void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView) const;
	void SetupAnimInstance();
	/** END preview scene setup */
	
	/** centralized management of selection across skeleton view and viewport */
	TSharedRef<FIKRigEditorController> EditorController;

	/** Preview scene to be supplied by IHasPersonaToolkit::GetPersonaToolkit */
	TSharedPtr<IPersonaToolkit> PersonaToolkit;
	
	friend FIKRigMode;
	friend SIKRigSkeleton;
	friend SIKRigSolverStack;
};
